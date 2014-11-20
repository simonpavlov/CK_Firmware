#include "../CK_PasswordPair.h"

#include <iostream>
#include <cstring>

// #define DEBUG_IO_PASSWORDPAIR

/*
PasswordPair::PasswordPair(Message *msg){
	#ifdef DEBUG_IO_PASSWORDPAIR
	std::cout << "IN PasswordPair::PasswordPair()" << std::endl;
	#endif //DEBUG_IO_PASSWORDPAIR

	uint8_t *data = (uint8_t *) msg->get_data();

	login		= String(data);
	password	= String(data + sizeof(uint32_t) + login.buf_size());
}
*/

PasswordPair::PasswordPair(const String &login_init, const String &passwd_init){
	login = login_init;
	password = passwd_init;
}

/*
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
*/

OByteStream & operator<<(OByteStream &stream, const PasswordPair &pass_pr){
	// TODO: нужна оптимизация, следующие две строки нужно переделать так, что бы
	// stream.write() вызывался один раз, сейчас вызывается два раза

	stream << pass_pr.login;
	stream << pass_pr.password;

	return stream;
}

IByteStream & operator>>(IByteStream &stream, PasswordPair &pass_pr){
	// TODO: нужна оптимизация, следующие две строки нужно переделать так, что бы
	// stream.read() вызывался один раз, сейчас вызывается четыре раза

	stream >> pass_pr.login;
	stream >> pass_pr.password;

	return stream;
}
