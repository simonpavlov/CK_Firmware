#ifndef EMUL_MANAGER
#define EMUL_MANAGER

#include <SDL/SDL.h>
#include "emulator.h"

//Realization in src/manager.c

static const char VIDEO_SYS		= 0x01;
static const char EEPROM_SYS	= 0x02;
static const char STORAGE_SYS	= 0x04;
static const char NETWORK_SYS	= 0x08;

/*
 * Статус инициализации 
 */
typedef enum {
    ALL_RIGHT = 0,	//Всё в порядке
    VIDEO_ERROR,	//Ошибка
    STORAGE_ERROR,	//Ошибка
    EEPROM_ERROR,	//Ошибка
    NETWORK_ERROR	//Ошибка
} InitStatus;

/*
 * Инициализация эмулятора, параметры - ширина и высота эктана
 * returns: случае неудачи вернёт *_ERROR
 */
InitStatus emul_init(unsigned char new_system_status); 

/*
 * Завершение работы эмулятора
 */
void emul_quit(unsigned char system_off);

#endif
