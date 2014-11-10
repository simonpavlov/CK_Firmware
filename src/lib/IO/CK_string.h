#ifndef CK_STRING
#define CK_STRING

#include <stdint.h>

class CK_string{
	private:
		uint32_t str_size;
		uint16_t *data;

	public:
		CK_string(const uint8_t *buf_init);
		uint8_t *	serialize();
		uint32_t	size(){return str_size;}
		uint16_t &	operator[](uint32_t n){return *(data + n);}
};

#endif //CK_STRING
