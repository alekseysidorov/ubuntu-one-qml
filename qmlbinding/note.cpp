#include "note.h"
#include "notes.h"

Note::Note(Notes *notes) :
	QObject(notes),
	m_notes(notes)
{
}

Note::Note(const QByteArray &guid, Notes *notes) :
	QObject(notes),
	m_notes(notes),
	m_guid(guid)
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

void Note::update()
{
}

void Note::remove()
{
}

