#include "../CK_String.h"

CK_String::CK_String(const uint8_t *buf_init){
	uint8_t *buf_r	= (uint8_t *)buf_init;
	uint8_t *buf_w	= (uint8_t *)&buf_len;

	for(uint32_t i = 0; i < sizeof(buf_len); i++) *buf_w++ = *buf_r++;

	if(buf_len + 1){
		str_size = buf_len / 2;

		data = new uint16_t[str_size];
	
		buf_w = (uint8_t *) data;
		for(uint32_t i = 0; i < buf_len; i++) *buf_w++ = *buf_r++;
	}
	else{
		str_size = 0;
		data = 0L;
	}
}

uint8_t * CK_String::serialize(){
	if(!(buf_len + 1)) return 0;

	uint8_t *res_buf = new uint8_t[sizeof(str_size) + buf_len];

	uint8_t *buf_r	= (uint8_t *)&buf_len;
	uint8_t *buf_w	= res_buf;

	for(uint32_t i = 0; i < sizeof(buf_len); i++) *buf_w++ = *buf_r++;

	buf_r = (uint8_t *)data;
	for(uint32_t i = 0; i < buf_len; i++) *buf_w++ = *buf_r++;

	return res_buf;
}

std::ostream & operator<<(std::ostream &stream, const CK_String &str){
	for(uint32_t i = 0; i < str.str_size; i++){
		if(*(str.data + i) >> 8) stream << "0x" << std::hex << *(str.data + i);
		else stream << char(*(str.data + i));
	}

	return stream;
}