#include "evernoteauth.h"

#include <QDebug>
#include <UserStore_types.h>
#include <transport/THttpTransport.h>

#define EDAM_CONSUMER_KEY "sauronthedark"
#define EDAM_CONSUMER_SECRET "cc6d71938cea7a1e"

//#define EVERNOTE_URL "https://sandbox.evernote.com"

using namespace apache::thrift;
using namespace apache::thrift::protocol;
using namespace apache::thrift::transport;

using namespace Evernote;

EvernoteAuth::EvernoteAuth(QObject *parent) :
	QObject(parent)
{
}

void EvernoteAuth::login()
{
	const wchar_t * userStoreUrl   = L"https://www.evernote.com/edam/user";

	AuthenticationResult result;
	result.IsGood = false;

	try
	{
		THttpTransport  transport (userStoreUrl);
		TBinaryProtocol protocol  (transport);
		transport.Open();

		EDAM::UserStore::UserStore::Client userStore(protocol);

		bool versionOk = userStore.checkVersion
			( L"Peoples' Note"
			, EDAM::UserStore::constants.EDAM_VERSION_MAJOR
			, EDAM::UserStore::constants.EDAM_VERSION_MINOR
			);
		if (!versionOk)
		{
			result.Message = L"Incompatible EDAM client protocol version\n";
			return result;
		}

		EDAM::UserStore::AuthenticationResult authenticationResult
			= userStore.authenticate
			( username
			, password
			, consumerKey
			, consumerSecret
			);

		result.IsGood  = true;
		result.ShardId = authenticationResult.user.shardId;
		result.Token   = authenticationResult.authenticationToken;
	}
	catch (const Thrift::Transport::TTransportException &)
	{
		logger.AuthorizationError(username, logger.GetExceptionMessage().Message);
		result.Message = L"Network error";
	}
	catch (const EDAM::Error::EDAMUserException &)
	{
		logger.AuthorizationError(username, logger.GetExceptionMessage().Message);
		result.Message = L"Invalid username or password";
	}
	catch (const TException &)
	{
		logger.AuthorizationError(username, logger.GetExceptionMessage().Message);
		result.Message = L"Something went wrong";
	}
	return result;
}

