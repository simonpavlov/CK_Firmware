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
		unsigned char *glyphs;		//ссылка на начало карт символов

	public:

		/*
			Считывает шрифт psf v2 из буфера buffer и инициализируется им.
		*/
		Font(const unsigned char *buffer);

		/*
			Функция для отладки, выводит шрифт в stdout
		*/
		void stdout();

		/*
			Генерирует поверхность из символа
		*/
		Surface & gen_char_surf(char &ch);

		/*
			Генерирует поверхность из строки
		*/
		Surface & gen_string_surf(std::string &str);
};


#endif //UI_FONT