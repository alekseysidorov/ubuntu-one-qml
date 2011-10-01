#include "note.h"

Note::Note(QObject *parent) :
    QObject(parent)
{
}

Note::Note(const QByteArray &guid, QObject *parent) :
	QObject(parent),
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

void Note::setText(const QString &text)
{
	m_text = text;
	emit textChanged();
}

QString Note::text() const
{
	return m_text;
}

