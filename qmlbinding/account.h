#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <QObject>
#include <QVariant>

class UbuntuOneApi;
class Account : public QObject
{
    Q_OBJECT
	Q_PROPERTY(QVariant info READ info NOTIFY infoUpdated)
public:
	explicit Account(UbuntuOneApi *auth);
	QVariant info() const;
public slots:
	void updateInfo() const;
signals:
	void infoUpdated(const QVariant &info);
private slots:
	void onInfoReceived();
private:
	UbuntuOneApi *m_api;
	QVariant m_info;
};

#endif // ACCOUNT_H
