#ifndef CK_ARRAY
#define CK_ARRAY

#include <stdint.h>

/*
	Этот класс реализует линейный буффер
*/
class Array{
	private:
		uint32_t	m_size; //размер буффера
		uint8_t		*m_data; //сам буфер
	public:
		Array();
		Array(const Array &arr);
		Array(uint8_t *data, uint32_t size);

		uint8_t &	operator[](uint32_t n){return *(m_data + n);} //возвращает n-й элемент
		Array &		operator=(const Array &arr);

		uint32_t	size(){return m_size;}
		uint8_t *	data(){return m_data;}	

		~Array();
};

#endif //CK_ARRAY
