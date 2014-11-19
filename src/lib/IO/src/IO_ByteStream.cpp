#include "../IO_ByteStream.h"

bool oByteStream::write(const uint8_t *buf, uint32_t size){
	return m_arr->app_end(buf, size);
}