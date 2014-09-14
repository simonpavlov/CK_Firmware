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
 * Возвращает указатель на структуру описывающую экран
 */
ScreenInfo * get_screen_info();

/*
 * Синхронизирует буфер и экран
 */
void refresh_video_buffer();

#endif
