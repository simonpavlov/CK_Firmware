#ifndef CK_PASSWORDPAIR
#define CK_PASSWORDPAIR

#include "CK_String.h"
#include "IO_ByteStream.h"
#include "IO_Message.h"

#include <string>

//Realization in src/CK_PasswordPair.cpp

class PasswordPair{
	public:
		String login;
		String password;

		PasswordPair(){}
		// PasswordPair(Message *msg);
		PasswordPair(const String &login_init, const String &passwd_init);
		PasswordPair(const std::string str): login(str) {}

		// Message * to_message();

		friend OByteStream & operator<<(OByteStream &stream, const PasswordPair &pass_pr);
		friend IByteStream & operator>>(IByteStream &stream, PasswordPair &pass_pr);
};

#endif //CK_PASSWORDPAIR
