#ifndef WEBKITAUTH_H
#define WEBKITAUTH_H

#include <QWebView>

class WebkitAuth : public QWebView
{
    Q_OBJECT
public:
	explicit WebkitAuth(const QUrl &url, QNetworkAccessManager *manager, QWidget *parent = 0);
	void setLoginData(const QString &email, const QString &password);
	void showExpanded();
signals:
	void finished(bool success);
private slots:
	void onLoadFinished(bool);
private:
	QString m_email;
	QString m_password;
};

#endif // WEBKITAUTH_H
