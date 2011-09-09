#include "qmlbinding_plugin.h"
#include "quickevernote.h"

#include <QtDeclarative/qdeclarative.h>

void QmlbindingPlugin::registerTypes(const char *uri)
{
	qmlRegisterType<QuickEvernote>(uri, 0, 1, "QuickEvernote");
}

Q_EXPORT_PLUGIN2(Qmlbinding, QmlbindingPlugin)

