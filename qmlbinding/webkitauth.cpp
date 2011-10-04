#include "webkitauth.h"
#include <QWebFrame>
#include <QWebElement>

#include <QDebug>

WebkitAuth::WebkitAuth(const QUrl &url, QNetworkAccessManager *manager, QWidget *parent) :
    QWebView(parent)
{
	setAttribute(Qt::WA_DeleteOnClose);

	QWebPage *p = page();
	p->setNetworkAccessManager(manager);
	p->mainFrame()->load(url);
	setWindowTitle(tr("Web authorization"));

	connect(p, SIGNAL(loadFinished(bool)), SLOT(onLoadFinished(bool)));
}

void WebkitAuth::onLoadFinished(bool)
{
	qDebug() << url().path();
	setWindowTitle(title());
	if (url().path() == QLatin1String("/dashboard/")) {
		emit finished(true);
		close();
	} else {
		QWebFrame *frame = page()->mainFrame();
		QWebElement email = frame->findFirstElement("#id_email");
		email.setAttribute("value", m_email);
		QWebElement pass = frame->findFirstElement("#id_password");
		pass.setAttribute("value", m_password);

		QWebElement submit = frame->findFirstElement("#continue");
		submit.setFocus();
		//submit.evaluateJavaScript("click()");
	}
}

void WebkitAuth::setLoginData(const QString &email, const QString &password)
{
	m_email = email;
	m_password = password;
}
