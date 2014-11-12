#include "../IO_PasswordPair.h"

#include <iostream>
#include <cstring>

// #define DEBUG_IO_PASSWORDPAIR

PasswordPair::PasswordPair(Message *msg){
	#ifdef DEBUG_IO_PASSWORDPAIR
	std::cout << "IN PasswordPair::PasswordPair()" << std::endl;
	#endif //DEBUG_IO_PASSWORDPAIR

	uint8_t *data = (uint8_t *) msg->get_data();

	login		= CK_String(data);
	password	= CK_String(data + sizeof(uint32_t) + login.buf_size());
}

PasswordPair::PasswordPair(const CK_String &login_init, const CK_String &passwd_init){
	login = login_init;
	password = passwd_init;
}

Message * PasswordPair::to_message(){
	uint32_t buf_len		= sizeof(uint32_t) + login.buf_size() + sizeof(uint32_t) + password.buf_size();

	uint8_t *buf			= new uint8_t[buf_len];
	uint8_t *buf_login		= login.serialize();
	uint8_t *buf_password	= password.serialize();

	uint8_t *buf_w = buf;

	for(int i = 0, i_max = sizeof(uint32_t) + login.buf_size(); i < i_max; i++) *buf_w++ = *buf_login++;
	for(int i = 0, i_max = sizeof(uint32_t) + password.buf_size(); i < i_max; i++) *buf_w++ = *buf_password++;

	return new Message(MessageType::PasswordGet, buf_len, buf);
}