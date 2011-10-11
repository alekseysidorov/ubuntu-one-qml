#include "note.h"
#include "notes.h"
#include <QUuid>

Note::Note(Notes *notes) :
	QObject(notes),
	m_notes(notes),
	m_status(StatusNew),
	m_isMarkedForRemoral(false)
{
	QUuid uid = QUuid::createUuid();
	m_guid = uid.toString();
}

Note::Note(const QString &guid, Notes *notes) :
	QObject(notes),
	m_notes(notes),
	m_guid(guid),
	m_status(StatusOutdated),
	m_isMarkedForRemoral(false)
{
}

void Note::setTitle(const QString &title)
{
	m_title = title;
	emit titleChanged();
}

QString Note::title() const
{
	return m_title;
}

void Note::setContent(const QString &text)
{
	m_content = text;
	emit textChanged();
}

QString Note::content() const
{
	return m_content;
}

QString Note::guid() const
{
	return m_guid;
}

int Note::revision() const
{
	return m_revision;
}

void Note::setRevision(int revision)
{
	m_revision = revision;
	emit revisionChanged();
}

Note::Status Note::status() const
{
	return m_status;
}

void Note::setStatus(Note::Status status)
{
	m_status = status;
	emit statusChanged();
}

QVariantMap Note::serialize(Note *note, bool saveGuid)
{
	QVariantMap map;
	if (saveGuid)
		map.insert("guid", note->guid());
	map.insert("title", note->title());
	map.insert("note-content", note->content());
	//map.insert("last-sync-revision", note->revision());
	if (note->isMarkedForRemoral())
		map.insert("command", "delete");
	return map;
}

void Note::fill(Note *note, const QVariantMap &data)
{
	//note->setGuid(data.value("guid"));
	note->setTitle(data.value("title").toString());
	note->setContent(data.value("note-content").toString());
	note->setRevision(data.value("last-sync-revision").toInt());
}

bool Note::isMarkedForRemoral() const
{
	return m_isMarkedForRemoral;
}

void Note::markForRemoral(bool set)
{
	m_isMarkedForRemoral = set;
}

void Note::save()
{
	sync();
}

void Note::remove()
{
	markForRemoral(true);
	sync();
}

void Note::sync()
{
	NoteList list;
	list.append(this);
	m_notes->updateNotes(list);
}

