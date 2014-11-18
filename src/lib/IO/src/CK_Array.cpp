#include "../CK_Array.h"
// #include <cstdlib>
#include <cstring>

#define DEBUG_CK_ARRAY

Array::Array():
	m_size(0),
	m_data(NULL)
{
	#ifdef DEBUG_CK_ARRAY
	std::cout << "IN Array::Array()" << std::endl;
	#endif // DEBUG_CK_ARRAY
}

Array::Array(uint32_t size):
	m_size(size)
{
	#ifdef DEBUG_CK_ARRAY
	std::cout << "IN Array::Array(uint32_t size)" << std::endl;
	#endif // DEBUG_CK_ARRAY

	m_data = new uint8_t[size];
	memset(m_data, 0, size);
}

Array::Array(const Array &arr):
	m_size(arr.m_size)
{
	#ifdef DEBUG_CK_ARRAY
	std::cout << "IN Array::Array(const Array &arr)" << std::endl;
	#endif // DEBUG_CK_ARRAY

	m_data = new uint8_t[m_size];
	memcpy(m_data, arr.m_data, m_size);
}

Array::Array(uint8_t *data, uint32_t size):
	m_size(size),
	m_data(data)
{
	#ifdef DEBUG_CK_ARRAY
	std::cout << "IN Array::Array(uint8_t *data, uint32_t size)" << std::endl;
	#endif // DEBUG_CK_ARRAY
}

uint8_t & Array::operator[](uint32_t n){
	return *(m_data + n);
}

Array &	Array::operator=(const Array &arr){
	#ifdef DEBUG_CK_ARRAY
	std::cout << "IN Array::operator=(const Array &arr)" << std::endl;
	#endif // DEBUG_CK_ARRAY

	m_size = arr.m_size;

	m_data = new uint8_t[m_size];
	memcpy(m_data, arr.m_data, m_size);

	return *this;
}

bool Array::app_end(const uint8_t *buf, uint32_t size){
	#ifdef DEBUG_CK_ARRAY
	std::cout << "IN Array::app_end(const uint8_t *buf, uint32_t size)" << std::endl;
	#endif // DEBUG_CK_ARRAY

	uint8_t *new_data;
	new_data = new uint8_t[m_size + size];

	memcpy(new_data, m_data, m_size);
	memcpy(new_data + m_size, buf, size);

	m_size = m_size + size;
	m_data = new_data;

	return (m_data != NULL);
}

bool Array::app_end(const Array &arr){
	return app_end(arr.m_data, arr.m_size);
}

Array::~Array(){
	#ifdef DEBUG_CK_ARRAY
	std::cout << "IN Array::~Array()" << std::endl;
	#endif // DEBUG_CK_ARRAY

	delete [] m_data;
}

std::ostream & operator<<(std::ostream &stream, const Array &arr){
	stream << "{ size:" << arr.m_size;
	if(arr.m_size && arr.m_size + 1){
		stream << ", data:";
		for(int i = 0; i < arr.m_size; i++) stream << std::hex << " 0x" << (int)*(arr.m_data + i);
		stream << " }";
		stream << std::dec;
	}

	return stream;
}