#ifndef CK_PASSWORDPAIR
#define CK_PASSWORDPAIR

#include "CK_String.h"
#include "IO_Message.h"

class PasswordPair{
	public:
		String login;
		String password;

		PasswordPair(Message *msg);
		PasswordPair(const String &login_init, const String &passwd_init);

		Message * to_message();

		friend oByteStream & operator<<(oByteStream &stream, const PasswordPair &pass_pr);
		// friend iByteStream & operator>>(iByteStream &stream, const PasswordPair &pass_pr);
};

#endif //CK_PASSWORDPAIR
