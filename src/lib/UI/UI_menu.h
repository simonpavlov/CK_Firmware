#ifndef CKF_MENU
#define CKF_MENU

#include "UI_font.h"
#include "UI_surface.h"

/*
Инициализация меню
*/
void menu_init(UI_surface *surf, CKF_Font *font);

/*
Перерисовывает меню
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

#endif
