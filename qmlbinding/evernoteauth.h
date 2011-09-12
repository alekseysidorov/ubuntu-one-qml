#ifndef EVERNOTEAUTH_H
#define EVERNOTEAUTH_H

#include <QObject>

class AuthWorker : public QObject
{
	Q_OBJECT
public:
	AuthWorker(QObject *parent = 0);

signals:
	void finished();
};

class EvernoteAuth : public QObject
{
    Q_OBJECT
public:
    explicit EvernoteAuth(QObject *parent = 0);

	void setLogin(const QString &login);
	QString login() const;
	void setPasswd(const QString &passwd);
	QString passwd() const;
	Q_INVOKABLE void login();
signals:
	void finished();
	void passwdChanged(const QString &now, const QString &old);
	void loginChanged(const QString &now, const QString &old);
private:
	QString m_passwd;
	QString m_login;
};

#endif // EVERNOTEAUTH_H
