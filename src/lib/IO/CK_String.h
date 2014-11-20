#ifndef CK_STRING
#define CK_STRING

#include <stdint.h>
#include <iostream>
#include "IO_ByteStream.h"

class String{
	private:
		uint32_t m_size;	// Длинна строки
		uint32_t buf_len;	// Длинна буфера
		uint16_t *data;		// !!! строка 16-ти битная

	public:
		String();
		String(const uint8_t *buf_init);
		String(const String &str);

		~String();


		uint8_t *	serialize();
		uint32_t	size(){return m_size;}
		uint32_t	buf_size(){return buf_len;}
		uint16_t &	operator[](uint32_t n){return *(data + n);}
		String & operator=(const String &str);

		friend OByteStream & operator<<(OByteStream &stream, const String &str);
		friend IByteStream & operator>>(IByteStream &stream, String &str);

		friend std::ostream & operator<<(std::ostream &stream, const String &str);
};

#endif //CK_STRING
