#include "auth.h"
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <qauthenticator.h>
#include <QStringBuilder>

#include <QDebug>
#include <json.h>
#include <QtOAuth>

Auth::Auth(QObject *parent) :
	QObject(parent),
	m_manager(new QNetworkAccessManager(this))
{
	connect(m_manager, SIGNAL(authenticationRequired(QNetworkReply*,QAuthenticator*)), SLOT(authenticationRequired(QNetworkReply*,QAuthenticator*)));
}

void Auth::login()
{
	QUrl url("https://login.ubuntu.com/api/1.0/authentications");
	url.addQueryItem(QLatin1String("ws.op"), QLatin1String("authenticate"));
	url.addQueryItem(QLatin1String("token_name"), QLatin1Literal("Ubuntu One ") % m_machineName);
	QNetworkRequest request(url);
	QNetworkReply *reply = m_manager->get(request);

	connect(reply, SIGNAL(finished()), SLOT(authReplyFinished()));
}

QString Auth::machineName() const
{
	return m_machineName;
}

QString Auth::password() const
{
	return m_password;
}

QString Auth::userName() const
{
	return m_userName;
}

void Auth::setMachineName(const QString &machine)
{
	m_machineName = machine;
	emit machineNameChanged();
}

void Auth::setPassword(const QString &password)
{
	m_password = password;
	emit passwordChanged();
}

void Auth::setUserName(const QString &name)
{
	m_userName = name;
	emit userNameChanged();
}

void Auth::authenticationRequired(QNetworkReply *reply, QAuthenticator *auth)
{
	auth->setUser(m_userName);
	auth->setPassword(m_password);
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

	QUrl url("https://one.ubuntu.com/oauth/sso-finished-so-get-tokens/" + m_userName);
	qDebug() << url.toEncoded();
	connect(get(url), SIGNAL(finished()), SLOT(onConfirmReplyFinished()));
}

void Auth::onConfirmReplyFinished()
{
	QNetworkReply *reply = static_cast<QNetworkReply*>(sender());
	qDebug() << reply->readAll();
	QUrl url("https://one.ubuntu.com/api/account/");
	connect(get(url), SIGNAL(finished()), SLOT(onTestReplyFinished()));
}

QNetworkReply *Auth::get(const QUrl &url)
{
	QOAuth::Interface oauth;
	oauth.setConsumerKey(m_consumerKey);
	oauth.setConsumerSecret(m_consumerSecret);
	QByteArray header = oauth.createParametersString(url.toEncoded(), QOAuth::GET, m_token, m_tokenSecret,
										QOAuth::HMAC_SHA1, QOAuth::ParamMap(),
										QOAuth::ParseForHeaderArguments);
	qDebug() << header;
	QNetworkRequest request(url);
	request.setRawHeader("Authorization", header);
	return m_manager->get(request);
}

void Auth::onTestReplyFinished()
{
	QNetworkReply *reply = static_cast<QNetworkReply*>(sender());
	qDebug() << reply->readAll();
	QVariant variant = Json::parse(reply->readAll());
	qDebug() << variant;
}

