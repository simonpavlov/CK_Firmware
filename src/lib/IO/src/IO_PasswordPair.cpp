#include "../IO_PasswordPair.h"

PasswordPair::PasswordPair(Message *msg){
	uint8_t *data = (uint8_t *) msg->get_data();

	login		= CK_String(data);
	password	= CK_String(data + sizeof(uint32_t) + login.buf_size());
}

Message * PasswordPair::to_message(){
	uint32_t buf_len		= sizeof(uint32_t) + login.buf_size() + sizeof(uint32_t) + password.buf_size();

	uint8_t *buf			= new uint8_t[buf_len];
	uint8_t *buf_login		= login.serialize();
	uint8_t *buf_password	= password.serialize();

	for(int i = 0, i_max = sizeof(uint32_t) + login.buf_size(); i < i_max; i++) *buf++ = *buf_login++;
	for(int i = 0, i_max = sizeof(uint32_t) + password.buf_size(); i < i_max; i++) *buf++ = *buf_password++;

	return new Message(MessageType::PasswordGet, buf_len, buf);
}