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
	Q_ASSERT(uri == QLatin1String("com.ubuntu.one"));

	qmlRegisterType<UbuntuOneApi>(uri, 1, 0, "Api");
	qmlRegisterType<ProgressIndicatorBase>(uri, 1, 0, "ProgressIndicatorBase");

	qmlRegisterUncreatableType<Notes>(uri, 1, 0, "Notes", tr("Use Api.notes property"));
	qmlRegisterUncreatableType<Account>(uri, 1, 0, "Account", tr("Use Api.account property"));
	qmlRegisterUncreatableType<Note>(uri, 1, 0, "Note", tr(""));
	qmlRegisterUncreatableType<NotesModel>(uri, 1, 0, "NotesModel", tr(""));
}

Q_EXPORT_PLUGIN2(qmlbinding, QmlBinding)
