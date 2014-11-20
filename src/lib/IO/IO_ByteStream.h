#ifndef IO_BYTESTREAM
#define IO_BYTESTREAM

#include "stdint.h"
#include "CK_Array.h"

/*
	Этто класс-обёртка он реализует поток чтения из буфера
*/
class IByteStream{
	private:
		Array	*m_arr;

	public:
		IByteStream(Array *arr): m_arr(arr) {}
		bool read(uint8_t *buf, uint32_t size);
};

/*
	Этто класс-обёртка он реализует поток ввода в буфер
*/
class OByteStream{
	private:
		Array	*m_arr;

	public:
		OByteStream(Array *arr): m_arr(arr) {}
		bool write(const uint8_t *buf, uint32_t size);
};

#endif //IO_BYTESTREAM
