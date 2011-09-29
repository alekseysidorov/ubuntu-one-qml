#ifndef NOTES_H
#define NOTES_H

#include <QObject>

class UbuntuOneApi;
class Notes : public QObject
{
    Q_OBJECT
public:
	explicit Notes(UbuntuOneApi *auth);
public slots:
	void sync();
private slots:
	void webLogin();
	void apiRefsReceived();
	void onNotesReceived();
	void onWebAuthFinished(bool success);
private:
	UbuntuOneApi *m_api;
	QString m_userName;
	QString m_firstName;
	QString m_lastName;
	QString m_notesRef;
	QString m_apiRef;
	int m_latestSyncRevision;
	QByteArray m_currentSyncGuid;
};

#endif // NOTES_H
