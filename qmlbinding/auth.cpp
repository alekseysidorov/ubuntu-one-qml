#include "auth.h"
#include "notes.h"
#include "account.h"

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
	m_manager(new QNetworkAccessManager(this)),
	m_oauth(new QOAuth::Interface(this))
{
	connect(m_manager, SIGNAL(authenticationRequired(QNetworkReply*,QAuthenticator*)),
			SLOT(onAuthenticationRequired(QNetworkReply*,QAuthenticator*)));
	connect(m_manager, SIGNAL(finished(QNetworkReply*)), SLOT(onReplyFinished(QNetworkReply*)));

	QSettings settings;
	settings.beginGroup("token");
	//TODO use encrypted storage instead
	m_oauth->setConsumerKey(settings.value("consumerKey").toByteArray());
	m_oauth->setConsumerSecret(settings.value("consumerSecret").toByteArray());

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

	connect(reply, SIGNAL(finished()), SLOT(onAuthReplyFinished()));
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

void Auth::onAuthenticationRequired(QNetworkReply *reply, QAuthenticator *auth)
{
	auth->setUser(reply->property("userName").toString());
	auth->setPassword(reply->property("password").toString());
}

void Auth::onAuthReplyFinished()
{
	QNetworkReply *reply = static_cast<QNetworkReply*>(sender());
	QVariantMap response = Json::parse(reply->readAll()).toMap();
	qDebug() << response;
	m_token = response.value("token").toByteArray();
	m_tokenSecret = response.value("token_secret").toByteArray();
	m_oauth->setConsumerKey(response.value("consumer_key").toByteArray());
	m_oauth->setConsumerSecret(response.value("consumer_secret").toByteArray());

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
		settings.setValue("consumerKey", m_oauth->consumerKey());
		settings.setValue("consumerSecret", m_oauth->consumerSecret());
		settings.setValue("token", m_token);
		settings.setValue("tokenSecret", m_tokenSecret);
		settings.endGroup();
	} else
		emit tokenRequestFailed();
}

QNetworkReply *Auth::get(const QUrl &url)
{
	QByteArray header = m_oauth->createParametersString(url.toEncoded(), QOAuth::GET, m_token, m_tokenSecret,
										QOAuth::HMAC_SHA1, QOAuth::ParamMap(),
										QOAuth::ParseForInlineQuery);

	QByteArray data = url.toEncoded().append(header);
	qDebug() << data;
	QNetworkRequest request(QUrl::fromEncoded(data));
	//request.setRawHeader("Authorization", header);
	return m_manager->get(request);
}

QNetworkReply *Auth::put(const QUrl &url, const QByteArray &data)
{
	QByteArray header = m_oauth->createParametersString(url.toEncoded(), QOAuth::GET, m_token, m_tokenSecret,
										QOAuth::HMAC_SHA1, QOAuth::ParamMap(),
										QOAuth::ParseForHeaderArguments);
	QNetworkRequest request(url);
	request.setRawHeader("Authorization", header);
	return m_manager->put(request, data);
}

void Auth::onTestReplyFinished()
{
	QNetworkReply *reply = static_cast<QNetworkReply*>(sender());

	QByteArray data = reply->readAll();
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

Account * Auth::account()
{
	if (!m_account)
		m_account = new Account(this);
	return m_account.data();
}

void Auth::onReplyFinished(QNetworkReply *reply)
{
	qDebug() << reply->attribute(QNetworkRequest::RedirectionTargetAttribute);
	QString r = reply->attribute(QNetworkRequest::RedirectionTargetAttribute).toString();
	if (!r.isEmpty())
		emit redirect(r);
}

void Auth::getApiRefs()
{
}

void Auth::onApiRefsReceived()
{
}

