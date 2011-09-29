#include "webkitauth.h"
#include <QWebFrame>

#include <QDebug>

WebkitAuth::WebkitAuth(const QUrl &url, QNetworkAccessManager *manager, QWidget *parent) :
    QWebView(parent)
{
	setAttribute(Qt::WA_DeleteOnClose);

	QWebPage *p = page();
	p->setNetworkAccessManager(manager);
	p->mainFrame()->load(url);

	connect(p, SIGNAL(loadFinished(bool)), SLOT(onLoadFinished(bool)));
}

void WebkitAuth::onLoadFinished(bool)
{
	qDebug() << url().path();
	if (url().path() == QLatin1String("/dashboard/")) {
		emit finished(true);
		close();
	}
}
