#ifndef UI_SURFACE
#define UI_SURFACE

#include <emul/emulator.h>

class Surface{
private:
	bool			memory_is_my;

	unsigned char	*buffer; // Ссылка на буфер в котором хранится поверхность
	unsigned int	width, height; // Ширина, высота
	unsigned int	buf_size; // Размер буфера

public:
	/*
		Инициализирует и связывает поверхность с ScreenInfo
	*/
	Surface(ScreenInfo &scr);

	/*
		Создаём поверхность размером w на h
	*/
	Surface(unsigned int w, unsigned int h);

	~Surface();

	/*
		Следующие функции возвращают соответствующие значения
	*/
	unsigned char * get_buffer() {return buffer;}
	unsigned char get_width() {return width;}
	unsigned char get_height() {return height;}
	unsigned char get_buf_size() {return buf_size;}
};

#endif //UI_SURFACE
