#ifndef EMUL_VIDEO
#define EMUL_VIDEO

#include <SDL/SDL.h>

/*
 * Структуря хроняшая в себе информацию о экране устройства
 */
typedef struct {
	char *buffer;	//Ссылка на видео буффер
	int width;		//Ширина дисплея
	int height;		//Высота дисплея
	int len_byte;	//Объём видео буфера
} ScreenInfo;

/*
 *	Устанавливает ширину и высоту для дисплея для инициализации
 */
void set_screen_res(unsigned int wth, unsigned int hht);

/*
 *	Инициализирует видео подсистему
 */
char video_init();

/*
 *	Возвращает указатель на структуру описывающую экран
 */
ScreenInfo * get_screen_info();

/*
 *	Синхронизирует буфер и экран
 */
void refresh_video_buffer();

/*
 *	Завершение работы видио системы
 */
void video_quit();

#endif
