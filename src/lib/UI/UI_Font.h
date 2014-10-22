#ifndef UI_FONT
#define UI_FONT

#include "UI_Surface.h"

#include <string>

class Font{
	private:
		unsigned int length;        //количество символов
		unsigned int char_size;     //количество байт на символ
		unsigned int height, width; //высота, ширина символов
		unsigned int width_byte;	//байтов на строку символа
		const unsigned char *glyphs;		//ссылка на начало карт символов

	public:
		/*
			Считывает шрифт psf v2 из буфера buffer и инициализируется им.
		*/
		Font(const unsigned char *buffer);

		/*
			Следующие функции возвращают соответствующие значения
		*/
		int get_width()		{return width;}
		int get_height()	{return height;}

		/*
			Функция для отладки, выводит шрифт в stdout
		*/
		void stdout();

		/*
			Генерирует поверхность из символа
		*/
		Surface & gen_surf(char ch);

		/*
			Генерирует поверхность из строки
			max_count - максимальное количество отрисовываемых символов
			max_width - максимальная ширина результирующей поверхности
		*/
		Surface & gen_surf(std::string str, unsigned int max_width = 0, unsigned int max_size = 0);
};


#endif //UI_FONT