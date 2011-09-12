#include <QtGui/QApplication>
#include "qmlapplicationviewer.h"

#include <QDebug>

#include <QtDeclarative>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

	QmlApplicationViewer viewer;

	//HACK
	QDir dir("../qmlbinding");
	foreach (QString plugin, dir.entryList()) {
		QString error;
		viewer.engine()->importPlugin(dir.absoluteFilePath(plugin), QLatin1String("EvernoteAPI"), &error);
		qDebug() << error << dir.absoluteFilePath(plugin);
	}

	viewer.setOrientation(QmlApplicationViewer::ScreenOrientationAuto);
	viewer.setMainQmlFile(QLatin1String("qml/client/main.qml"));
	viewer.showExpanded();
	return app.exec();
}
