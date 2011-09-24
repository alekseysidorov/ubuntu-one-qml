#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <QObject>
#include <QVariant>

class Auth;
class Account : public QObject
{
    Q_OBJECT
	Q_PROPERTY(QVariant info READ info NOTIFY infoUpdated)
public:
	explicit Account(Auth *auth);
	QVariant info() const;
public slots:
	void updateInfo() const;
signals:
	void infoUpdated(const QVariant &info);
private slots:
	void onInfoReceived();
private:
	Auth *m_auth;
	QVariant m_info;
};

#endif // ACCOUNT_H
