#include "note.h"
#include "notes.h"

Note::Note(Notes *notes) :
	QObject(notes),
	m_notes(notes),
	m_status(NoteNew)
{
}

Note::Note(const QByteArray &guid, Notes *notes) :
	QObject(notes),
	m_notes(notes),
	m_guid(guid),
	m_status(NoteOutdated)
{
}

void Note::setTitle(const QString &title)
{
	m_title = title;
	emit titleChanged();
}

QString Note::title() const
{
	return m_title;
}

void Note::setContent(const QString &text)
{
	m_content = text;
	emit textChanged();
}

QString Note::content() const
{
	return m_content;
}

QString Note::guid() const
{
	return m_guid;
}

int Note::revision() const
{
	return m_revision;
}

void Note::setRevision(int revision)
{
	m_revision = revision;
	emit revisionChanged();
}

Note::Status Note::status() const
{
	return m_status;
}

void Note::setStatus(Note::Status status)
{
	m_status = status;
	emit statusChanged();
}

void Note::save()
{
}

void Note::remove()
{
}

void Note::sync()
{
}

