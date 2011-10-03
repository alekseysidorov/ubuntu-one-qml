#include "notesstorage.h"
#include "note.h"

NotesStorage::NotesStorage(Notes *notes) :
	m_notes(notes)
{
	if (!checkStorage())
		initStorage();
}

void NotesStorage::save(Note *note)
{
}

void NotesStorage::save(const NoteList &notes)
{
}

NoteList NotesStorage::load(bool loadContent)
{
	return NoteList();
}

Note *NotesStorage::load(const QByteArray &guid, bool loadContent)
{
	Note *note = new Note(guid, m_notes);
	return note;
}

bool NotesStorage::checkStorage() const
{
	return false; //TODO
}

void NotesStorage::initStorage()
{
	//TODO
}
