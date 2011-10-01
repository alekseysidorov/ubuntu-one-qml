#ifndef NOTE_H
#define NOTE_H

#include <QObject>

class Notes;
class Note : public QObject
{
	Q_OBJECT

	Q_PROPERTY(QString title READ title WRITE setTitle NOTIFY titleChanged)
	Q_PROPERTY(QString content READ content WRITE setContent NOTIFY textChanged)
public:
	explicit Note(Notes *notes);
	explicit Note(const QByteArray &guid, Notes *notes);
	void setTitle(const QString &title);
	QString title() const;
	void setContent(const QString &content);
	QString content() const;
signals:
	void titleChanged();
	void textChanged();
public slots:
	void update();
	void remove();
private:
	Notes *m_notes;
	QByteArray m_guid;
	QString m_title;
	QString m_content;
};

#endif // NOTE_H
