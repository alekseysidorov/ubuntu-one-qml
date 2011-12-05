#ifndef NOTES_H
#define NOTES_H

#include <QObject>
#include <QWeakPointer>
#include <QVariantMap>

class Note;
typedef QList<Note*> NoteList;
class NotesModel;
class UbuntuOneApi;
class Notes : public QObject
{
    Q_OBJECT
	Q_PROPERTY(NotesModel* model READ model NOTIFY modelChanged)
	Q_PROPERTY(bool busy READ isBusy NOTIFY busyChanged)
public:
	explicit Notes(UbuntuOneApi *auth);
	NotesModel *model();
	void updateNotes(const NoteList &notes);
	void setBusy(bool busy);
	bool isBusy() const;
signals:
	void modelChanged();
	void syncFinished();
	void busyChanged();
protected:
	Note *fillNote(const QVariantMap &map);
public slots:
	void sync();
	Note *create();
private slots:
	void webLogin();
	void apiRefsReceived();
	void onNotesReceived();
	void onWebAuthFinished(bool success);
	void onNotesUpdateFinished();
private:
	UbuntuOneApi *m_api;
	QWeakPointer<NotesModel> m_model;

	QString m_userName;
	QString m_firstName;
	QString m_lastName;
	QString m_notesRef;
	QString m_apiRef;

	int m_latestSyncRevision;
	QByteArray m_currentSyncGuid;
	bool m_busy;
};

#endif // NOTES_H
