#ifndef NOTE_H
#define NOTE_H

#include <QObject>

class Note : public QObject
{
	Q_OBJECT

	Q_PROPERTY(QString title READ title WRITE setTitle NOTIFY titleChanged)
	Q_PROPERTY(QString text READ text WRITE setText NOTIFY textChanged)
public:
	explicit Note(QObject *parent = 0);
	explicit Note(const QByteArray &guid, QObject *parent = 0);
	void setTitle(const QString &title);
	QString title() const;
	void setText(const QString &text);
	QString text() const;
signals:
	void titleChanged();
	void textChanged();
public slots:
	void update();
	void remove();
private:
	QByteArray m_guid;
	QString m_title;
	QString m_text;

};

#endif // NOTE_H
