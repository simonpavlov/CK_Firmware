#ifndef EMUL_MANAGER
#define EMUL_MANAGER

#include <SDL/SDL.h>

typedef enum {
    ALL_RIGHT = 0,
    SDL_ERROR,
    NO_MEMORY_ERROR
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
