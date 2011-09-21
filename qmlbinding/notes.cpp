#include "notes.h"
#include "auth.h"

Notes::Notes(Auth *auth) : QObject(auth),
	m_auth(auth)
{
}
