#ifndef WEBKITAUTH_H
#define WEBKITAUTH_H

#include <QWebView>

class WebkitAuth : public QWebView
{
    Q_OBJECT
public:
	explicit WebkitAuth(const QUrl &url, QNetworkAccessManager *manager, QWidget *parent = 0);
signals:
	void finished(bool success);
private slots:
	void onLoadFinished(bool);

};

#endif // WEBKITAUTH_H
