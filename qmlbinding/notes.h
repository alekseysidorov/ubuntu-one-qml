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
public:
	explicit Notes(UbuntuOneApi *auth);
	NotesModel *model();
	void updateNotes(const NoteList &notes);
signals:
	void modelChanged();
	void syncFinished();
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
};

#endif // NOTES_H
