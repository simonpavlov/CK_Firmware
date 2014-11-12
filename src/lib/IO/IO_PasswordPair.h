#ifndef IO_PASSWORDPAIR
#define IO_PASSWORDPAIR

#include "CK_String.h"
#include "IO_Message.h"

class PasswordPair{
	public:
		CK_String login;
		CK_String password;

		PasswordPair(Message *msg);
		PasswordPair(const CK_String &login_init, const CK_String &passwd_init);

		Message * to_message();
};

#endif //IO_PASSWORDPAIR
