#ifndef CK_STRING
#define CK_STRING

#include <stdint.h>
#include <iostream>

class CK_String{
	private:
		uint32_t str_size;	// Длинна строки
		uint32_t buf_len;	// Длинна буфера
		uint16_t *data;		// !!! строка 16-ти битная

	public:
		CK_String();
		CK_String(const uint8_t *buf_init);
		CK_String(const CK_String &str);

		~CK_String();


		uint8_t *	serialize();
		uint32_t	size(){return str_size;}
		uint32_t	buf_size(){return (buf_len + 1)? buf_len: 0;}
		uint16_t &	operator[](uint32_t n){return *(data + n);}
		CK_String & operator=(const CK_String &str);

		friend std::ostream & operator<<(std::ostream &stream, const CK_String &str);
};

#endif //CK_STRING
