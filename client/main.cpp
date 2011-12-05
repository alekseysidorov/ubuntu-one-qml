#include <QtGui/QApplication>
#include "qmlapplicationviewer.h"

#include <QDebug>

#include <QtDeclarative>
#include <QDebug>
#include <QIcon>
#include <QLibraryInfo>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
	app.setApplicationName("wanderer");
	app.setApplicationVersion("0.1");
	app.setOrganizationName("sauron");
	app.setOrganizationDomain("http://co-de.org");

	QmlApplicationViewer viewer;

	qDebug() << viewer.engine()->importPathList();
	qDebug() << QLibraryInfo::location(QLibraryInfo::PluginsPath);

	//HACK
	QDir dir(app.applicationDirPath() + "/../qmlbinding");
	foreach (QString plugin, dir.entryList()) {
		QString error;
		viewer.engine()->importPlugin(dir.absoluteFilePath(plugin), QLatin1String("com.ubuntu.one"), &error);
		if (error.isEmpty())
			qWarning("Hack load");
	}
	if (QIcon::themeName().isEmpty())
		QIcon::setThemeName("oxygen");

	viewer.setOrientation(QmlApplicationViewer::ScreenOrientationAuto);
	viewer.setMainQmlFile(QLatin1String("qml/client/main.qml"));
	//viewer.setMinimumSize(300, 400);
	viewer.showExpanded();
	return app.exec();
}
