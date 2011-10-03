#include "notesmodel.h"
#include "note.h"

NotesModel::NotesModel(QObject *parent) :
	QObjectListModel(parent)
{
	QHash<int, QByteArray> roles;
	roles[ObjectRole] = "note";
	setRoleNames(roles);
}

Note *NotesModel::find(const QByteArray &guid)
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
	foreach (auto *note, notes)
		append(note);
}

void NotesModel::append(Note *note)
{
	if (!contains(note))
		QObjectListModel::append(note);
}
