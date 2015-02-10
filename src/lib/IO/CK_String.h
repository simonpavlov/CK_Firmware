#ifndef CK_STRING
#define CK_STRING

#include <stdint.h>
#include <iostream>
#include "IO_ByteStream.h"

//Realization in src/CK_String.cpp

class String{
	private:
		uint32_t m_size;		// Длинна строки
		uint32_t m_data_len;	// Длинна буфера
		uint16_t *m_data;		// !!! строка 16-ти битная

	public:
		String();
		String(const char *c_str);
		String(const String &str);

		~String();


		// uint8_t *	serialize();
		uint32_t	size() const {return m_size;}
		uint32_t	buf_size() const {return m_data_len;}
		uint16_t &	operator[](uint32_t n){return *(m_data + n);}
		String &	operator=(const String &str);
		uint16_t *	operator&(){return m_data;}

		friend OByteStream & operator<<(OByteStream &stream, const String &str);
		friend IByteStream & operator>>(IByteStream &stream, String &str);

		friend std::ostream & operator<<(std::ostream &stream, const String &str);
};

#endif //CK_STRING
