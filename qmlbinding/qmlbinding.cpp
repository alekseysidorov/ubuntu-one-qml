#include "qmlbinding.h"
#include "auth.h"
#include "notes.h"

#include <QtDeclarative>

#include <QDebug>

QmlBinding::QmlBinding()
{
	qDebug() << Q_FUNC_INFO;
}

void QmlBinding::registerTypes(const char *uri)
{
	Q_ASSERT(uri == QLatin1String("UbuntuOne"));
	qmlRegisterType<Auth>(uri, 0, 1, "Auth");
	qmlRegisterUncreatableType<Notes>(uri, 0, 1, "Notes", tr("Use auth.notes property"));
}

Q_EXPORT_PLUGIN2(qmlbinding, QmlBinding)
