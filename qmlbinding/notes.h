#ifndef NOTES_H
#define NOTES_H

#include <QObject>

class Auth;
class Notes : public QObject
{
    Q_OBJECT
public:
	explicit Notes(Auth *auth);
private:
	Auth *m_auth;
};

#endif // NOTES_H
