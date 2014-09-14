#ifndef CKF_UI
#define CKF_UI

#include "UI_tree.h"
#include "UI_font.h"
#include "UI_menu.h"
#include "UI_surface.h"
#include <emul/emulator.h>

/*
Инициализация пользовательского интерфейса
*/
void UI_init(ScreenInfo *screen, CKF_Font *font);

/*
Обработать нажатие вверх
*/
void UI_up();

/*
Обработать нажатие вниз
*/
void UI_down();

/*
Обработать нажатие ввод
*/
void UI_enter();

/*
Отрисовка поьзовательского интерфейса
*/
void UI_draw();

/*
Очищает видео буфер
*/
void UI_clear_scr();

#endif