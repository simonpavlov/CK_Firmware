#ifndef EMUL_MANAGER
#define EMUL_MANAGER

#include <SDL/SDL.h>

/*
 * Статус инициализации 
 */
typedef enum {
    ALL_RIGHT = 0,	//Всё в порядке
    SDL_ERROR,		//Ошибка в SDL
    NO_MEMORY_ERROR	//Ошибка выделения памяти
} InitStatus;

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
 * Инициализация эмулятора, параметры - ширина и высота эктана
 * returns: случае неудачи вернёт *_ERROR
 */
InitStatus emul_init(int width, int height); 

/*
 * Завершение работы эмулятора
 */
void emul_quit();

#endif
