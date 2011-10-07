#include "notes.h"
#include "note.h"
#include "notesmodel.h"
#include "notesstorage.h"
#include "auth.h"
#include <QNetworkReply>
#include <json.h>
#include "webkitauth.h"

#include <QDebug>

Notes::Notes(UbuntuOneApi *auth) : QObject(auth),
	m_api(auth),
	m_latestSyncRevision(0),
	m_currentRevision(0)
{
}

NotesModel *Notes::model()
{
	if (!m_model) {
		m_model = new NotesModel(this);
		NotesStorage storage(this);
		m_model.data()->append(storage.load());
		emit modelChanged();
	}
	return m_model.data();
}

void Notes::updateNotes(const NoteList &notes)
{
	QVariantMap map;
	map.insert("latest-sync-revision", m_latestSyncRevision);
	QVariantList list;
	foreach (Note *note, notes) {
		note->setStatus(note->isMarkedForRemoral() ? Note::NoteRemoral : Note::NoteSyncing);
		list.append(Note::serialize(note));
	}
	map.insert("note-changes", list);
	QByteArray data = Json::generate(map);

	qDebug() << data;

	QUrl url(m_apiRef);
	connect(m_api->put(url, data), SIGNAL(finished()), SLOT(onNotesUpdateFinished()));
}

void Notes::sync()
{
	if (m_apiRef.isEmpty()) {
		QUrl url("https://one.ubuntu.com/notes/api/1.0/user/"); //TODO get ref from auth
		connect(m_api->get(url), SIGNAL(finished()), SLOT(apiRefsReceived()));
		return;
	}

	QUrl url(m_apiRef);
	url.addQueryItem("since", QString::number(m_latestSyncRevision));
	url.addQueryItem("include_notes", "true");
	qDebug() << url;
	connect(m_api->get(url), SIGNAL(finished()), SLOT(onNotesReceived()));
}

Note *Notes::create()
{
	Note *note = new Note(this);
	note->setTitle(tr("New note"));
	note->setContent(tr("Type here"));
	model()->append(note);
	return note;
}

void Notes::apiRefsReceived()
{
	QByteArray data = static_cast<QNetworkReply*>(sender())->readAll();
	QVariantMap map = Json::parse(data).toMap();
	m_userName = map.value("user-name").toString();
	m_lastName = map.value("last-name").toString();
	m_firstName = map.value("first-name").toString();
	m_currentSyncGuid = map.value("current-sync-guid").toByteArray();
	m_currentRevision = map.value("latest-sync-revision").toInt();

	QVariantMap notes = map.value("notes-ref").toMap();
	m_notesRef = notes.value("href").toString();
	m_apiRef = notes.value("api-ref").toString();
	qDebug() << data;

	sync();
}

void Notes::onNotesReceived()
{
	QByteArray data = static_cast<QNetworkReply*>(sender())->readAll();
	if (data.isEmpty())
		webLogin();
	else {
		QVariantMap map = Json::parse(data).toMap();
		m_currentRevision = m_latestSyncRevision = map.value("latest-sync-revision").toInt();
		QVariantList notes = map.value("notes").toList();
		NoteList list;
		foreach (QVariant value, notes) {
			Note *note = fillNote(value.toMap());
			if (note)
				list.append(note);
		}
		model()->append(list);
	}
	emit syncFinished();
}

void Notes::webLogin()
{
	WebkitAuth *webAuth = new WebkitAuth(QUrl("https://one.ubuntu.com/auth/login"), m_api->manager());
	webAuth->setLoginData(m_api->email(), m_api->pasword());
	webAuth->show();
	connect(webAuth, SIGNAL(finished(bool)), SLOT(onWebAuthFinished(bool)));
}

void Notes::onWebAuthFinished(bool success)
{
	if (success)
		sync();
}

void Notes::onNotesUpdateFinished()
{
	QNetworkReply *reply = static_cast<QNetworkReply*>(sender());
	qDebug() << reply->readAll();
}

Note *Notes::fillNote(const QVariantMap &map)
{
	QByteArray guid = map.value("guid").toByteArray();
	if (guid.isEmpty())
		return 0;
	int revision = map.value("last-sync-revision").toInt();


	Note *note = model()->find(guid);
	if (!note)
	   note = new Note(guid, this);
	else if (note->revision() >= revision)
		return note;

	Note::fill(note, map);
	qDebug() << guid << note->title();
	return note;
}
