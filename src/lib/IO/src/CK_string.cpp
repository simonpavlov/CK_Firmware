#include "../CK_string.h"

CK_string::CK_string(const uint8_t *buf_init){
	uint8_t *buf_r	= (uint8_t *)buf_init;
	uint8_t *buf_w	= (uint8_t *)&str_size;

	for(int i = 0; i < sizeof(str_size); i++) *buf_w++ = *buf_r++;

	data = new uint16_t[str_size];

	buf_w = (uint8_t *) data;
	for(int i = 0; i < 2 * str_size; i++) *buf_w++ = *buf_r++;
}

uint8_t * CK_string::serialize(){
	uint8_t *res_buf = new uint8_t[sizeof(str_size) + 2 * str_size];

	uint8_t *buf_r	= (uint8_t *)&str_size;
	uint8_t *buf_w	= res_buf;

	for(int i = 0; i < sizeof(str_size); i++) *buf_w++ = *buf_r++;

	buf_r = (uint8_t *)data;
	for(int i = 0; i < str_size * 2; i++) *buf_w++ = *buf_r++;

	return res_buf;
}
