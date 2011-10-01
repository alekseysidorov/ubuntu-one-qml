#ifndef NOTESMODEL_H
#define NOTESMODEL_H

#include <qobjectlistmodel.h>
#include <QVariant>

class NotesModel : public QObjectListModel
{
	Q_OBJECT
public:
	explicit NotesModel(QObject *parent = 0);
	
signals:
	
public slots:
	
};

#endif // NOTESMODEL_H
