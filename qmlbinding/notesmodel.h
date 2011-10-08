#ifndef NOTESMODEL_H
#define NOTESMODEL_H

#include <qobjectlistmodel.h>
#include <QVariant>

class Note;
typedef QList<Note*> NoteList;
class NotesModel : public QObjectListModel
{
	Q_OBJECT
public:
	explicit NotesModel(QObject *parent = 0);
	Note *find(const QByteArray &guid);
	void append(const NoteList &notes);
	void append(Note *note);
	void remove(Note *note);
private slots:
	void onNoteRemoved(QObject *object);
};

#endif // NOTESMODEL_H
