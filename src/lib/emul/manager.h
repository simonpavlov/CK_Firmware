#ifndef EMUL_MANAGER
#define EMUL_MANAGER

#include <SDL/SDL.h>
#include "video.h"

/*
 * Статус инициализации 
 */
typedef enum {
    ALL_RIGHT = 0,	//Всё в порядке
    SDL_ERROR,		//Ошибка в SDL
    NO_MEMORY_ERROR	//Ошибка выделения памяти
} InitStatus;

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
