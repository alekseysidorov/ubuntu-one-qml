#ifndef QUICKEVERNOTE_H
#define QUICKEVERNOTE_H

#include <QtDeclarative/QDeclarativeItem>

class QuickEvernote : public QDeclarativeItem
{
    Q_OBJECT
    Q_DISABLE_COPY(QuickEvernote)

public:
    QuickEvernote(QDeclarativeItem *parent = 0);
    ~QuickEvernote();
};

QML_DECLARE_TYPE(QuickEvernote)

#endif // QUICKEVERNOTE_H

