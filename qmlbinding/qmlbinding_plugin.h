#ifndef QMLBINDING_PLUGIN_H
#define QMLBINDING_PLUGIN_H

#include <QtDeclarative/QDeclarativeExtensionPlugin>

class QmlbindingPlugin : public QDeclarativeExtensionPlugin
{
    Q_OBJECT

public:
    void registerTypes(const char *uri);
};

#endif // QMLBINDING_PLUGIN_H

