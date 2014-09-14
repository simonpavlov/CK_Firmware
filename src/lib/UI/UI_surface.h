#ifndef UI_SURFACE
#define UI_SURFACE

/*
	Структура хронящая в себе описание поверхности
*/
typedef struct {
	char	*buffer;		// Ссылка на буфер в котором хранится поверхность
	int		width, height;	// Ширина, высота
	int		len_byte;		// Объём бкфера в байтах
} UI_surface;

/*
	Инициализация поверхности
	w - ширина
	h - высота
*/
UI_surface * UI_surf_init(int w, int h);

/*
	Удаление поверхности
*/
void UI_surf_free(UI_surface * surf);

/*
	Отрисовка поверхности на экране
*/
//TODO: обработку выхода за пределы экрана
//TODO: обработку поверхностей ширина которых не кратна 8
void UI_draw_surf(UI_surface * surf, int x, int y);

/*
	Стирает всё с поверхности
*/
void UI_clear_surf(UI_surface *surf);

/*
	Ресует границцы поверхности на ней самой
*/
//TODO: обработку поверхностей ширина которых не кратна 8
void UI_border(UI_surface *surf);

#endif
