#include "notesstorage.h"
#include "note.h"
#include <QtSql>
#include <QDesktopServices>

namespace {

bool isExist(Note *note)
{
	QSqlQuery query;
	query.prepare("SELECT id FROM notes WHERE guid = ?");
	query.addBindValue(note->guid());
	if (!query.exec()) {
		qWarning() << query.lastError();
	bool ok = query.next();
	qDebug() << query.size();
	return ok;
}

int lastInsertId(const QString &table)
{
	QSqlQuery query(QString("SELECT max(id) FROM %1").arg(table));
	if (!query.exec()) {
		qWarning() << query.lastError();
	}
	return query.next() ? query.value(0).toInt() : -1;
}

int getNoteId(const QString &guid)
{
	QSqlQuery query;
	query.prepare("SELECT id FROM notes WHERE guid = ?");
	query.addBindValue(guid);
	if (!query.exec()) {
		qWarning() << query.lastError();
	}
	return query.next() ? query.value(0).toInt() : -1;
}

void saveNote(Note *note)
{
	QSqlQuery query;
	query.prepare("INSERT INTO notes(guid) VALUES (?)");
	query.addBindValue(note->guid());
	if (!query.exec()) {
		qWarning() << query.lastError();
		//TODO
	}

	int id = lastInsertId("notes");
	QVariantMap properties = Note::serialize(note, false);
	for (auto it = properties.constBegin(); it != properties.constEnd(); it++) {
		query.prepare("INSERT INTO properties(noteid, key, value) VALUES(?, ?, ?)");
		query.addBindValue(id);
		query.addBindValue(it.key());
		query.addBindValue(it.value());
		if(!query.exec())
			qDebug() << query.lastError();
	}
}

void updateNote(Note *note)
{
	int id = getNoteId(note->guid());
	QVariantMap properties = Note::serialize(note, false);
	for (auto it = properties.constBegin(); it != properties.constEnd(); it++) {
		QSqlQuery query;
		query.prepare("UPDATE properies SET value = ? WHERE noteid = ? AND key = ?");
		query.addBindValue(it.value());
		query.addBindValue(id);
		query.addBindValue(it.key());
		if(!query.exec())
			qDebug() << query.lastError();
	}
}

QVariantMap getNoteProperties(int noteid, bool includeContent = true)
{
	QVariantMap map;
	if (includeContent) {
		QSqlQuery propQuery;
		propQuery.prepare("SELECT key, value FROM properties WHERE noteid = ?");
		propQuery.addBindValue(noteid);
		propQuery.exec();
		while (propQuery.next())
			map.insert(propQuery.value(0).toString(), propQuery.value(1).toString());
	} else {
		QSqlQuery titleQuery;
		titleQuery.prepare("SELECT value FROM properties WHERE noteid = ? and key = ?");
		titleQuery.addBindValue(noteid);
		titleQuery.addBindValue("title");
		titleQuery.exec();
		if (titleQuery.next())
			map.insert("title", titleQuery.value(0));
	}
	return map;
}

QVariantMap getNoteData(const QByteArray &guid, bool includeContent = true)
{
	QVariantMap map = getNoteProperties(getNoteId(guid), includeContent);
	map.insert("guid", guid);
	return map;
}

QVariantList getNotes(bool includeContent = true)
{
	QVariantList list;
	QSqlQuery query;
	query.prepare("SELECT id, guid FROM notes");
	query.exec();
	while (query.next()) {
		int id = query.value(0).toInt();
		QVariantMap map = getNoteProperties(id, includeContent);
		map.insert("guid", query.value(1));
		list.append(map);
	}
	return list;
}

void removeNote(const QString &guid)
{
	QSqlQuery query;
	int noteid = getNoteId(guid);
	query.prepare("DELETE FROM notes WHERE id = ?");
	query.addBindValue(noteid);
	if (!query.exec()) {
		//TODO
		return;
	}
	query.prepare("DELETE FROM properties WHERE noteid = ?");
	query.addBindValue(noteid);
	if (!query.exec()) {
		//TODO
		return;
	}
}

} //namespace

NotesStorage::NotesStorage(Notes *notes) :
	m_notes(notes)
{
	if (!QSqlDatabase::contains()) {
		QSqlDatabase db = QSqlDatabase::addDatabase(QLatin1String("QSQLITE"));
		QString location(QDesktopServices::storageLocation(QDesktopServices::DataLocation));
		QDir dir(location);
		if (!dir.exists())
			dir.mkpath(location);
		QString path = location % QLatin1Literal("/notes.db");
		db.setDatabaseName(path);
		if (!db.open()) {
			qDebug() << db.lastError();
			//TODO notification (QMessagebox or MNotification)
			return;
		}
	}

	if (!checkStorage())
		initStorage();
}

void NotesStorage::save(Note *note)
{
	if (!isExist(note))
		saveNote(note);
	else
		updateNote(note);
}

void NotesStorage::save(const NoteList &notes)
{
	foreach (auto note, notes)
		saveNote(note);
}

NoteList NotesStorage::load(bool loadContent)
{
	NoteList list;
	foreach (QVariant data, getNotes(loadContent)) {
		QVariantMap map = data.toMap();
		Note *note = new Note(map.value("guid").toString(), m_notes);
		Note::fill(note, map);
		list.append(note);
	}
	return list;
}

void NotesStorage::remove(const QString &guid)
{
	removeNote(guid);
}

void NotesStorage::remove(const QList<QString> &notes)
{
	for (auto note : notes)
		remove(note);
}

Note *NotesStorage::load(const QByteArray &guid, bool loadContent)
{
	Note *note = new Note(guid, m_notes);
	Note::fill(note, getNoteData(guid, loadContent));
	return note;
}

bool NotesStorage::checkStorage() const
{
	QSqlQuery query;
	query.prepare("SELECT 1 FROM FROM notes");
	return query.exec();
}

void NotesStorage::initStorage()
{
	QFile file(QLatin1String(":/database/notes.sql"));
	if (!file.open(QIODevice::ReadOnly))
		qDebug() << "unable to open sql file";
	QString script(file.readAll());
	foreach (QString string, script.split(";")) {
		QSqlQuery query;
		query.prepare(string);
		query.exec();
	}
}
