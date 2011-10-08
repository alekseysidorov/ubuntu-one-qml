#ifndef NOTE_H
#define NOTE_H

#include <QObject>
#include <QVariant>

class Notes;
class Note : public QObject
{
	Q_OBJECT

	Q_PROPERTY(QString title READ title WRITE setTitle NOTIFY titleChanged)
	Q_PROPERTY(QString content READ content WRITE setContent NOTIFY textChanged)
	Q_PROPERTY(int revision READ revision NOTIFY revisionChanged)
	Q_PROPERTY(Status status READ status NOTIFY statusChanged)
	Q_ENUMS(Status)
public:
	enum Status
	{
		StatusNew,
		StatusActual,
		StatusOutdated,
		StatusSyncing,
		StatusRemoral
	};
	explicit Note(Notes *notes);
	explicit Note(const QByteArray &guid, Notes *notes);
	void setTitle(const QString &title);
	QString title() const;
	void setContent(const QString &content);
	QString content() const;
	QString guid() const;
	int revision() const;
	void setRevision(int revision);
	Status status() const;
	void setStatus(Status status);
	static QVariantMap serialize(Note *note);
	static void fill(Note *note, const QVariantMap &data);
	bool isMarkedForRemoral() const;
	void markForRemoral(bool set);
signals:
	void titleChanged();
	void textChanged();
	void revisionChanged();
	void saved();
	void statusChanged();
public slots:
	void save();
	void remove();
	void sync();
private:
	Notes *m_notes;
	QByteArray m_guid;
	QString m_title;
	QString m_content;
	int m_revision;
	Status m_status;
	bool m_isMarkedForRemoral;
};
typedef QList<Note*> NoteList;

Q_DECLARE_METATYPE(NoteList)

#endif // NOTE_H
