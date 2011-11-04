#include "qmlbinding.h"

#include "auth.h"
#include "notes.h"
#include "note.h"
#include "notesmodel.h"
#include "account.h"
#include "progressindicator.h"

#include <QtDeclarative>

#include <QDebug>

QmlBinding::QmlBinding()
{
	qDebug() << Q_FUNC_INFO;
}

void QmlBinding::registerTypes(const char *uri)
{
	Q_ASSERT(uri == QLatin1String("UbuntuOne"));

	qmlRegisterType<UbuntuOneApi>(uri, 0, 1, "Api");
	qmlRegisterType<ProgressIndicatorBase>(uri, 0, 1, "ProgressIndicatorBase");

	qmlRegisterUncreatableType<Notes>(uri, 0, 1, "Notes", tr("Use Api.notes property"));
	qmlRegisterUncreatableType<Account>(uri, 0, 1, "Account", tr("Use Api.account property"));
	qmlRegisterUncreatableType<Note>(uri, 0, 1, "Note", tr(""));
	qmlRegisterUncreatableType<NotesModel>(uri, 0, 1, "NotesModel", tr(""));
}

Q_EXPORT_PLUGIN2(qmlbinding, QmlBinding)
