#include "qmlbinding.h"
#include "evernoteauth.h"
#include <QtDeclarative>

#include <QDebug>

QmlBinding::QmlBinding()
{
	qDebug() << Q_FUNC_INFO;
}

void QmlBinding::registerTypes(const char *uri)
{
	Q_ASSERT(uri == QLatin1String("EvernoteAPI"));
	qmlRegisterType<EvernoteAuth>(uri, 0, 1, "Auth");
}

Q_EXPORT_PLUGIN2(qmlbinding, QmlBinding)
