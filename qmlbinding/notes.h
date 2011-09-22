#ifndef NOTES_H
#define NOTES_H

#include <QObject>

class Auth;
class Notes : public QObject
{
    Q_OBJECT
public:
	explicit Notes(Auth *auth);	
public slots:
	void sync();
private slots:
	void apiRefsReceived();
	void onNotesReceived();
private:
	Auth *m_auth;
	QString m_userName;
	QString m_firstName;
	QString m_lastName;
	QString m_notesRef;
	QString m_apiRef;
	int m_latestSyncRevision;
	QByteArray m_currentSyncGuid;
};

#endif // NOTES_H
