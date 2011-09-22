#include "auth.h"
#include "notes.h"

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <qauthenticator.h>
#include <QStringBuilder>

#include <QDebug>
#include <json.h>
#include <QtOAuth>
#include <QSettings>

Auth::Auth(QObject *parent) :
	QObject(parent),
	m_manager(new QNetworkAccessManager(this))
{
	connect(m_manager, SIGNAL(authenticationRequired(QNetworkReply*,QAuthenticator*)),
			SLOT(authenticationRequired(QNetworkReply*,QAuthenticator*)));
	connect(m_manager, SIGNAL(finished(QNetworkReply*)), SLOT(onReplyFinished(QNetworkReply*)));

	QSettings settings;
	settings.beginGroup("token");
	//TODO use encrypted storage instead
	m_consumerKey = settings.value("consumerKey").toByteArray();
	m_consumerSecret = settings.value("consumerSecret").toByteArray();
	m_token = settings.value("token").toByteArray();
	m_tokenSecret = settings.value("tokenSecret").toByteArray();
	settings.endGroup();
}

void Auth::requestToken(const QString &userName, const QString &password)
{
	QUrl url("https://login.ubuntu.com/api/1.0/authentications");
	url.addQueryItem(QLatin1String("ws.op"), QLatin1String("authenticate"));
	url.addQueryItem(QLatin1String("token_name"), QLatin1Literal("Ubuntu One @ ") % m_machineName);

	qDebug() << url.toEncoded();

	QNetworkRequest request(url);
	QNetworkReply *reply = m_manager->get(request);
	reply->setProperty("userName", userName);
	reply->setProperty("password", password);

	connect(reply, SIGNAL(finished()), SLOT(authReplyFinished()));
}

void Auth::test()
{
	QUrl url("https://one.ubuntu.com/api/account/");
	connect(get(url), SIGNAL(finished()), SLOT(onTestReplyFinished()));
}

QString Auth::machineName() const
{
	return m_machineName;
}


void Auth::setMachineName(const QString &machine)
{
	m_machineName = machine;
	emit machineNameChanged();
}

void Auth::authenticationRequired(QNetworkReply *reply, QAuthenticator *auth)
{
	auth->setUser(reply->property("userName").toString());
	auth->setPassword(reply->property("password").toString());
}

void Auth::authReplyFinished()
{
	QNetworkReply *reply = static_cast<QNetworkReply*>(sender());
	QVariantMap response = Json::parse(reply->readAll()).toMap();
	qDebug() << response;
	m_token = response.value("token").toByteArray();
	m_tokenSecret = response.value("token_secret").toByteArray();
	m_consumerKey = response.value("consumer_key").toByteArray();
	m_consumerSecret = response.value("consumer_secret").toByteArray();

	QUrl url("https://one.ubuntu.com/oauth/sso-finished-so-get-tokens/" + reply->property("userName").toString());
	qDebug() << url.toEncoded();
	connect(get(url), SIGNAL(finished()), SLOT(onConfirmReplyFinished()));
}

void Auth::onConfirmReplyFinished()
{
	QNetworkReply *reply = static_cast<QNetworkReply*>(sender());
	if (reply->readAll().contains("ok")) {
		emit receivedToken();

		QSettings settings;
		settings.beginGroup("token");
		settings.setValue("consumerKey", m_consumerKey);
		settings.setValue("consumerSecret", m_consumerSecret);
		settings.setValue("token", m_token);
		settings.setValue("tokenSecret", m_tokenSecret);
		settings.endGroup();
		test();
	} else
		emit tokenRequestFailed();
}

QNetworkReply *Auth::get(const QUrl &url)
{
	QOAuth::Interface oauth;
	oauth.setConsumerKey(m_consumerKey);
	oauth.setConsumerSecret(m_consumerSecret);
	QByteArray header = oauth.createParametersString(url.toEncoded(), QOAuth::GET, m_token, m_tokenSecret,
										QOAuth::HMAC_SHA1, QOAuth::ParamMap(),
										QOAuth::ParseForHeaderArguments);
	QNetworkRequest request(url);
	request.setRawHeader("Authorization", header);
	return m_manager->get(request);
}

QNetworkReply * Auth::put(const QUrl &url, const QByteArray &data)
{
	QOAuth::Interface oauth;
	oauth.setConsumerKey(m_consumerKey);
	oauth.setConsumerSecret(m_consumerSecret);
	QByteArray header = oauth.createParametersString(url.toEncoded(), QOAuth::GET, m_token, m_tokenSecret,
										QOAuth::HMAC_SHA1, QOAuth::ParamMap(),
										QOAuth::ParseForHeaderArguments);
	QNetworkRequest request(url);
	request.setRawHeader("Authorization", header);
	return m_manager->put(request, data);
}

void Auth::onTestReplyFinished()
{
	QNetworkReply *reply = static_cast<QNetworkReply*>(sender());
	qDebug() << reply->rawHeaderList();

	QByteArray data = reply->readAll();
	QVariant variant = Json::parse(data);
	qDebug() << data;
}

bool Auth::hasToken() const
{
	return !m_token.isEmpty();
}

Notes *Auth::notes()
{
	if (!m_notes)
		m_notes = new Notes(this);
	return m_notes.data();
}

void Auth::onReplyFinished(QNetworkReply *reply)
{
	qDebug() << reply->attribute(QNetworkRequest::RedirectionTargetAttribute);
	QString r = reply->attribute(QNetworkRequest::RedirectionTargetAttribute).toString();
	if (!r.isEmpty())
		emit redirect(r);
}

