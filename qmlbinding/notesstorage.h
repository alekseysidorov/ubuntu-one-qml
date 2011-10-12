#ifndef NOTESSTORAGE_H
#define NOTESSTORAGE_H
#include <QVariant>

class Note;
class Notes;
typedef QList<Note*> NoteList;

class NotesStorage
{
public:
	NotesStorage(Notes *notes);
	void save(Note *note);
	void save(const NoteList &notes);
	NoteList load(bool loadContent = true);
	Note *load(const QByteArray &guid, bool loadContent = true);
	void load(Note *note);
	void remove(const QString &guid);
	void remove(const QList<QString> &notes);
protected:
	bool checkStorage() const;
	void initStorage();
private:
	Notes *m_notes;
};

#endif // NOTESSTORAGE_H
