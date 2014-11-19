#ifndef IO_BYTESTREAM
#define IO_BYTESTREAM

#include "stdint.h"
#include "CK_Array.h"

/*
	Этто класс-обёртка он реализует поток чтения из буфера
*/
class iByteStream{
	private:
		Array	*m_arr;
		uint8_t	*cur_byte;

	public:
		iByteStream(Array *arr): m_arr(arr), cur_byte(arr->data()) {}
		bool read(uint8_t *buf, uint32_t size);
};

/*
	Этто класс-обёртка он реализует поток ввода в буфер
*/
class oByteStream{
	private:
		Array	*m_arr;

	public:
		oByteStream(Array *arr): m_arr(arr) {}
		bool write(const uint8_t *buf, uint32_t size);
};

#endif //IO_BYTESTREAM
