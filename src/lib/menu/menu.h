#ifndef CKF_MENU
#define CKF_MENU

#include "font.h"
#include <emul/emulator.h>

/*
Отдельный пункт меню
*/
typedef struct{
	struct CKF_MenuItem *next;
	struct CKF_MenuItem *prev;

	char 				*name;
	void 				(*call_back)();
	struct CKF_MenuList	*child;
}CKF_MenuItem;

/*
Лист меню
*/
typedef struct{
	struct CKF_MenuList *parent;

	struct CKF_MenuItem *vertex;
	int count;
}CKF_MenuList;

/*
Инициализация меню
*/
void menu_init(ScreenInfo *screen, CKF_Font *font);

/*
Отрисовка меню
*/
void menu_draw();

/*
Перемещение курсора на один пункт вверх
*/
void menu_up();

/*
Перемещение курсора на один пункт вниз
*/
void menu_down();

/*
Выбрать текущий пункт
*/
void menu_enter();

/*
Очищает видео буфер
*/
void clear_scr();

#endif
