#include "../IO_ByteStream.h"
#include <cstring>
#include <iostream>

bool IByteStream::read(uint8_t *buf, uint32_t size){
	return m_arr->take_front(buf, size);
}

bool OByteStream::write(const uint8_t *buf, uint32_t size){
	return m_arr->app_end(buf, size);
}