#include "notes.h"
#include "auth.h"
#include <QNetworkReply>
#include <json.h>
#include "webkitauth.h"

#include <QDebug>

Notes::Notes(UbuntuOneApi *auth) : QObject(auth),
	m_api(auth),
	m_latestSyncRevision(0)
{
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

void Notes::apiRefsReceived()
{
	QByteArray data = static_cast<QNetworkReply*>(sender())->readAll();
	QVariantMap map = Json::parse(data).toMap();
	m_userName = map.value("user-name").toString();
	m_lastName = map.value("last-name").toString();
	m_firstName = map.value("first-name").toString();
	m_currentSyncGuid = map.value("current-sync-guid").toByteArray();
	//m_latestSyncRevision = map.value("latest-sync-revision").toInt();

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
		qDebug() << map;
	}
}

void Notes::webLogin()
{
	WebkitAuth *webAuth = new WebkitAuth(QUrl("https://one.ubuntu.com/auth/login"), m_api->manager());
	webAuth->show();
	connect(webAuth, SIGNAL(finished(bool)), SLOT(onWebAuthFinished(bool)));
}

void Notes::onWebAuthFinished(bool success)
{
	if (success)
		sync();
}
