#include "qmlbinding.h"

#include "auth.h"
#include "notes.h"
#include "account.h"

#include <QtDeclarative>

#include <QDebug>

QmlBinding::QmlBinding()
{
	qDebug() << Q_FUNC_INFO;
}

void QmlBinding::registerTypes(const char *uri)
{
	Q_ASSERT(uri == QLatin1String("UbuntuOne"));
	qmlRegisterType<UbuntuOneApi>(uri, 0, 1, "Api");
	qmlRegisterUncreatableType<Notes>(uri, 0, 1, "Notes", tr("Use auth.notes property"));
	qmlRegisterUncreatableType<Account>(uri, 0, 1, "Account", tr("Use auth.account property"));
}

Q_EXPORT_PLUGIN2(qmlbinding, QmlBinding)
