/**
 * Autogenerated by Thrift
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 */
#ifndef UserStore_TYPES_H
#define UserStore_TYPES_H

#include <Thrift.h>
#include <TApplicationException.h>
#include <protocol/TProtocol.h>
#include <transport/TTransport.h>

#include "Types_types.h"
#include "Errors_types.h"


namespace evernote { namespace edam {

typedef struct _PublicUserInfo__isset {
  _PublicUserInfo__isset() : privilege(false), username(false) {}
  bool privilege;
  bool username;
} _PublicUserInfo__isset;

class PublicUserInfo {
 public:

  static const char* ascii_fingerprint; // = "724DFF4FFFB8A87B3EDA5AEF78D412EB";
  static const uint8_t binary_fingerprint[16]; // = {0x72,0x4D,0xFF,0x4F,0xFF,0xB8,0xA8,0x7B,0x3E,0xDA,0x5A,0xEF,0x78,0xD4,0x12,0xEB};

  PublicUserInfo() : userId(0), shardId(""), username("") {
  }

  virtual ~PublicUserInfo() throw() {}

  evernote::edam::UserID userId;
  std::string shardId;
  evernote::edam::PrivilegeLevel privilege;
  std::string username;

  _PublicUserInfo__isset __isset;

  bool operator == (const PublicUserInfo & rhs) const
  {
    if (!(userId == rhs.userId))
      return false;
    if (!(shardId == rhs.shardId))
      return false;
    if (__isset.privilege != rhs.__isset.privilege)
      return false;
    else if (__isset.privilege && !(privilege == rhs.privilege))
      return false;
    if (__isset.username != rhs.__isset.username)
      return false;
    else if (__isset.username && !(username == rhs.username))
      return false;
    return true;
  }
  bool operator != (const PublicUserInfo &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const PublicUserInfo & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _AuthenticationResult__isset {
  _AuthenticationResult__isset() : user(false), publicUserInfo(false) {}
  bool user;
  bool publicUserInfo;
} _AuthenticationResult__isset;

class AuthenticationResult {
 public:

  static const char* ascii_fingerprint; // = "1B3F4F8424E32630F5A30B0B5798E8DF";
  static const uint8_t binary_fingerprint[16]; // = {0x1B,0x3F,0x4F,0x84,0x24,0xE3,0x26,0x30,0xF5,0xA3,0x0B,0x0B,0x57,0x98,0xE8,0xDF};

  AuthenticationResult() : currentTime(0), authenticationToken(""), expiration(0) {
  }

  virtual ~AuthenticationResult() throw() {}

  evernote::edam::Timestamp currentTime;
  std::string authenticationToken;
  evernote::edam::Timestamp expiration;
  evernote::edam::User user;
  PublicUserInfo publicUserInfo;

  _AuthenticationResult__isset __isset;

  bool operator == (const AuthenticationResult & rhs) const
  {
    if (!(currentTime == rhs.currentTime))
      return false;
    if (!(authenticationToken == rhs.authenticationToken))
      return false;
    if (!(expiration == rhs.expiration))
      return false;
    if (__isset.user != rhs.__isset.user)
      return false;
    else if (__isset.user && !(user == rhs.user))
      return false;
    if (__isset.publicUserInfo != rhs.__isset.publicUserInfo)
      return false;
    else if (__isset.publicUserInfo && !(publicUserInfo == rhs.publicUserInfo))
      return false;
    return true;
  }
  bool operator != (const AuthenticationResult &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const AuthenticationResult & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

}} // namespace

#endif