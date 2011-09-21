#ifndef AUTH_H
#define AUTH_H

#include <QObject>
#include <QWeakPointer>

class QAuthenticator;
class QNetworkReply;
class QNetworkAccessManager;
class QUrl;

class Notes;
class AuthPrivate;
class Auth : public QObject
{
    Q_OBJECT
    
	Q_PROPERTY(QString machine READ machineName WRITE setMachineName NOTIFY machineNameChanged)
	Q_PROPERTY(bool hasToken READ hasToken)
	Q_PROPERTY(Notes *notes READ notes)
public:
    explicit Auth(QObject *parent = 0);
	void setMachineName(const QString &machine);
	QString machineName() const;
	bool hasToken() const;
	QNetworkReply *get(const QUrl &);
	Notes *notes();
public slots:
	void requestToken(const QString &userName, const QString &password);
	void test();
signals:
	void receivedToken();
	void tokenRequestFailed();
	void machineNameChanged();
	void tokenRequested();
private slots:
	void authenticationRequired(QNetworkReply *reply, QAuthenticator *auth);
	void authReplyFinished();
	void onConfirmReplyFinished();
	void onTestReplyFinished();
private:
	QString m_machineName;
	QByteArray m_token;
	QByteArray m_tokenSecret;
	QByteArray m_consumerKey;
	QByteArray m_consumerSecret;
	QNetworkAccessManager *m_manager;
	QWeakPointer<Notes> m_notes;
};

#endif // AUTH_H
