#include <QtGui/QApplication>
#include "qmlapplicationviewer.h"

#include <QDebug>

#include <QtDeclarative>
#include "../qmlbinding/evernoteauth.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

	qmlRegisterType<EvernoteAuth>("org.evernote.quick", 0, 1, "Auth");

    QmlApplicationViewer viewer;
    viewer.setOrientation(QmlApplicationViewer::ScreenOrientationAuto);
    viewer.setMainQmlFile(QLatin1String("qml/client/main.qml"));
	viewer.addImportPath(QLatin1String("../qmlbinding"));
    viewer.showExpanded();

	return app.exec();
}
