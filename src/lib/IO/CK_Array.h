#ifndef CK_ARRAY
#define CK_ARRAY

#include <stdint.h>
#include <iostream>

//Realization in src/CK_Array.cpp

/*
	Этот класс реализует линейный буффер
*/
class Array{
	private:
		uint32_t	m_size; //размер
		uint8_t		*m_data; //сам буфер

	public:
		Array();
		Array(uint32_t size);
		Array(const Array &arr);
		Array(uint8_t *data, uint32_t size);

		uint8_t &	operator[](uint32_t n); //возвращает n-й элемент
		Array &		operator=(const Array &arr);

		/*
			Переписывает из текушего массива в buf size бит и удаляет их из массива вернёт
			true если всё хорошо, иначе flase
		*/
		bool	take_front(uint8_t *buf, uint32_t size);

		/*
			Приписывает size бит от buf к текущему массиву, вернёт true если всё ок, иначе
			false
		*/
		bool		app_end(const uint8_t *buf, uint32_t size);
		bool		app_end(const Array &arr);

		uint32_t	size() const {return m_size;}
		uint8_t *	data() {return m_data;}

		~Array();

		friend std::ostream & operator<<(std::ostream &stream, const Array &arr);
};

#endif //CK_ARRAY
