#ifndef CKF_MENU
#define CKF_MENU

#include "font.h"

/*
Инициализация меню
*/
void menu_init(char *video_buffer, int width, int height, CKF_Font *font);

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
