#ifndef NOTE_H
#define NOTE_H

#include <QObject>

class Notes;
class Note : public QObject
{
	Q_OBJECT

	Q_PROPERTY(QString title READ title WRITE setTitle NOTIFY titleChanged)
	Q_PROPERTY(QString content READ content WRITE setContent NOTIFY textChanged)
	Q_PROPERTY(int revision READ revision NOTIFY revisionChanged)
public:
	explicit Note(Notes *notes);
	explicit Note(const QByteArray &guid, Notes *notes);
	void setTitle(const QString &title);
	QString title() const;
	void setContent(const QString &content);
	QString content() const;
	QString guid() const;
	int revision() const;
	void setRevision(int revision);
signals:
	void titleChanged();
	void textChanged();
	void revisionChanged();
	void saved();
public slots:
	void save();
	void remove();
private:
	Notes *m_notes;
	QByteArray m_guid;
	QString m_title;
	QString m_content;
	int m_revision;
};
typedef QList<Note*> NoteList;

#endif // NOTE_H
