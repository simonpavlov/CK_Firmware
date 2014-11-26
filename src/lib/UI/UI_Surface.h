#ifndef UI_SURFACE
#define UI_SURFACE

#include <string>

class Surface{
	protected:
		unsigned char	*buffer; // Ссылка на буфер в котором хранится поверхность
		unsigned int	width, height; // Ширина, высота
		unsigned int	buf_size; // Размер буфера
		bool			surf_is_my;

		/*
			Создаёт пусту поверхность
		*/
		Surface();

	public:

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
			Очистить часть экрана
		*/
		void clear(unsigned int x, unsigned int y, unsigned int w, unsigned int h);

		/*
			Отрисовка на данной поверхности поверхности surf
			по координатам x, y
		*/
		void draw(Surface &surf, unsigned int x, unsigned int y);

		/*
			Отрисовка на данной поверхности поверхности surf
			по середине
		*/
		void draw(Surface &surf);

		/*
			Отрисовать пиксель по заданным координатам
		*/
		void draw(unsigned int x, unsigned int y);

		/*
			Отрисовка паралелограмма по координатам x, y,
			шириной w, высотой h
		*/
		void draw(unsigned int x, unsigned int y, unsigned int w, unsigned int h);

		/*
			 Нарисовать границы поверхности
		*/
		void draw_border();
};

#endif //UI_SURFACE
