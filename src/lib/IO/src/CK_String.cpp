#include "../CK_String.h"

#include <cstring>

// #define DEBUG_CK_STRING

String::String():
	m_size(0),
	m_data_len(0),
	m_data(0)
{
	#ifdef DEBUG_CK_STRING
	std::cout << "IN String::String()" << std::endl;
	#endif //DEBUG_CK_STRING
}


String::String(const char *c_str){
	#ifdef DEBUG_CK_STRING
	std::cout << "IN String::String(const uint8_t *buf_init)" << std::endl;
	#endif //DEBUG_CK_STRING

	// uint8_t *buf_r	= (uint8_t *)buf_init;
	// uint8_t *buf_w	= (uint8_t *)&m_data_len;

	// for(uint32_t i = 0; i < sizeof(m_data_len); i++) *buf_w++ = *buf_r++;

	// if(m_data_len + 1){
	// 	m_size = m_data_len / 2;

	// 	m_data = new uint16_t[m_size];
	
	// 	buf_w = (uint8_t *) m_data;
	// 	for(uint32_t i = 0; i < m_data_len; i++) *buf_w++ = *buf_r++;
	// }
	// else{
	// 	m_size = 0;
	// 	m_data = 0L;
	// }

	uint32_t str_len = strlen(c_str);

	m_size		= str_len;
	m_data_len	= 2 * str_len;
	m_data		= new uint16_t[str_len];

	for(uint32_t i = 0; i < str_len; i++){
		*(m_data + i) = *(c_str + i);
	}

}

String::String(const String &str):
	m_size(str.m_size),
	m_data_len(str.m_data_len)
{
	#ifdef DEBUG_CK_STRING
	std::cout << "IN String::String(const String &str)" << std::endl;
	#endif //DEBUG_CK_STRING

	m_data = new uint16_t[m_size];
	memcpy(m_data, str.m_data, m_data_len);
}

String::~String(){
	#ifdef DEBUG_CK_STRING
	std::cout << "IN String::~String()" << std::endl;
	#endif //DEBUG_CK_STRING

	delete [] m_data;
}

/*
uint8_t * String::serialize(){
	uint8_t *res_buf;

	if(!(m_data_len + 1)){
		res_buf = new uint8_t[sizeof(m_size)];
		*((uint32_t *)res_buf) = ~0L;
	}
	else{
		res_buf = new uint8_t[sizeof(m_size) + m_data_len];

		uint8_t *buf_r;
		uint8_t *buf_w = res_buf;

		*((uint32_t *)buf_w) = m_data_len;
		buf_w += sizeof(m_data_len);

		buf_r = (uint8_t *)m_data;
		for(uint32_t i = 0; i < m_data_len; i++) *buf_w++ = *buf_r++;
	}

	return res_buf;
}
*/

String & String::operator=(const String &str){
	#ifdef DEBUG_CK_STRING
	std::cout << "IN String & operator=(const String &str)" << std::endl;
	#endif

	if(this == &str){
		return *this;
	}

	m_size		= str.m_size;
	m_data_len	= str.m_data_len;

	if(m_data) delete [] m_data;
	m_data = new uint16_t[m_size];

	memcpy(m_data, str.m_data, m_data_len);

	return *this;
}

OByteStream & operator<<(OByteStream &stream, const String &str){
	uint32_t	m_data_len;
	uint8_t		*buf;

	if(str.m_size){
		m_data_len	= sizeof(uint32_t) + str.m_data_len;
		buf			= new uint8_t[m_data_len];

		uint8_t *buf_w = buf;

		memcpy(buf_w, (uint8_t *)&str.m_data_len, sizeof(uint32_t));
		buf_w += sizeof(uint32_t);

		memcpy(buf_w, (uint8_t *)str.m_data, str.m_data_len);
	}
	else{
		m_data_len	= sizeof(uint32_t);
		buf		= new uint8_t[m_data_len];

		*((uint32_t *)buf) = ~0L;
	}

	stream.write(buf, m_data_len);

	delete [] buf;

	return stream;
}

IByteStream & operator>>(IByteStream &stream, String &str){
	uint16_t *str_data = str.m_data;

	uint32_t str_size;
	uint32_t buf_size;

	stream.read((uint8_t *)&buf_size, sizeof(buf_size));

	delete [] str_data;

	if(buf_size && buf_size + 1){
		str_size = buf_size / 2;
		str_data = new uint16_t[str_size];

		stream.read((uint8_t *)str_data, buf_size);
	}
	else{
		buf_size = 0;
		str_size = 0;
		str_data = NULL;
	}

	str.m_data_len	= buf_size;
	str.m_size	= str_size;
	str.m_data	= str_data;

	return stream;
}

std::ostream & operator<<(std::ostream &stream, const String &str){
	for(uint32_t i = 0; i < str.m_size; i++){
		if(*(str.m_data + i) >> 8) stream << "0x" << std::hex << *(str.m_data + i);
		else stream << char(*(str.m_data + i));
	}

	return stream;
}
