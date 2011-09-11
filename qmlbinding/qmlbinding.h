#ifndef QMLBINDING_H
#define QMLBINDING_H
#include <QDeclarativeExtensionPlugin>

class QmlBinding : public QDeclarativeExtensionPlugin
{
	Q_OBJECT
public:
	QmlBinding();
	virtual void registerTypes(const char *uri);
};

#endif // QMLBINDING_H
