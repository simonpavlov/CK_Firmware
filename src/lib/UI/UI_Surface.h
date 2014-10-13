#ifndef UI_SURFACE
#define UI_SURFACE

class Surface{
private:
	unsigned char	*buffer; // Ссылка на буфер в котором хранится поверхность
	unsigned int	width, height; // Ширина, высота
	unsigned int	buf_size; // Размер буфера

public:
	/*
		Создаём поверхность размером w на h
	*/
	Surface(unsigned int w, unsigned int h);

	/*
		Следующие функции возвращают соответствующие значения
	*/
	unsigned char * get_buffer() {return buffer;}
	unsigned char get_width() {return width;}
	unsigned char get_height() {return height;}
	unsigned char get_buf_size() {return buf_size;}

	~Surface();
};

#endif //UI_SURFACE
