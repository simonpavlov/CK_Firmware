#ifndef UI_SURFACE
#define UI_SURFACE

#include <emul/emulator.h>

#include <string>

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
		unsigned char	* get_buffer() {return buffer;}
		unsigned int	get_width() {return width;}
		unsigned int	get_height() {return height;}
		unsigned int	get_buf_size() {return buf_size;}

		/*
			Очистка поверхности
		*/
		void clear();

		/*
			Отрисовка на данной поверхности поверхности surf
			по координатам x, y
		*/
		void draw_surf(Surface &surf, unsigned int x, unsigned int y);

		/*
			Отрисовать пиксели по заданным координатам
		*/
		void draw_pix(unsigned int x, unsigned int y);

		/*
			Отрисовка паралелограмма по координатам x, y,
			шириной w, высотой h
		*/
		void draw_pargram(unsigned int x, unsigned int y, unsigned int w, unsigned int h);

		/*
			 Нарисовать границы поверхности
		*/
		void draw_border();
};

#endif //UI_SURFACE
