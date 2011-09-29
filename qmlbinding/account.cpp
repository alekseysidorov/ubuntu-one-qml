#include "account.h"
#include "auth.h"

#include <json.h>

#include <QNetworkReply>

Account::Account(UbuntuOneApi *auth) :
	QObject(auth),
	m_api(auth)
{
}

void Account::updateInfo() const
{
	connect(m_api->get(QUrl("https://one.ubuntu.com/api/account/")), SIGNAL(finished()),
			SLOT(onInfoReceived()));
}

void Account::onInfoReceived()
{
	QNetworkReply *reply = static_cast<QNetworkReply*>(sender());
	m_info = Json::parse(reply->readAll());
	emit infoUpdated(m_info);
}

QVariant Account::info() const
{
	if (m_info.isNull())
		updateInfo();
	return m_info;
}
