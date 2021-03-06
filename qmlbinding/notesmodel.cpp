#include "notesmodel.h"
#include "note.h"

NotesModel::NotesModel(QObject *parent) :
	QObjectListModel(parent)
{
	QHash<int, QByteArray> roles;
	roles[ObjectRole] = "note";
	setRoleNames(roles);
}

Note *NotesModel::find(const QString &guid)
{
	foreach (QObject *obj, objectList()) {
		Note *note = static_cast<Note*>(obj);
		if (note->guid() == guid)
			return note;
	}
	return 0;
}

void NotesModel::append(const NoteList &notes)
{
	foreach (auto note, notes)
		append(note);
}

void NotesModel::append(Note *note)
{
	if (!contains(note)) {
		QObjectListModel::append(note);
		connect(note, SIGNAL(destroyed(QObject*)), SLOT(onNoteRemoved(QObject*)));
	}
}

void NotesModel::remove(Note *note)
{
	int index = indexOf(note);
	if (index != -1)
		removeAt(index);
}

void NotesModel::onNoteRemoved(QObject *object)
{
	remove(static_cast<Note*>(object));
}
