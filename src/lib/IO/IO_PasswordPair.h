#ifndef IO_PASSWORDPAIR
#define IO_PASSWORDPAIR

#include "CK_String.h"
#include "IO_Message.h"

struct PasswordPair{
	CK_String login;
	CK_String password;

	PasswordPair(Message *msg);
	Message * to_message();
};

#endif //IO_PASSWORDPAIR
