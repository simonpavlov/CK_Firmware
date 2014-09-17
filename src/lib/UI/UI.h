#ifndef CKF_UI
#define CKF_UI

#include "UI_tree.h"
#include "UI_font.h"
#include "UI_menu.h"
#include "UI_surface.h"
#include <emul/emulator.h>

/*
	Отдельная задача, под задачей понимается: меню и различные
	всплывающий окна.
*/
struct UI_task{
	UI_surface *surf;
	void (* draw)();
	void (* press_up)();
	void (* press_down)();
	void (* press_enter)();
};

/*
	Отдельный элемент стека задач
*/
struct UI_stack_item{
	struct UI_task *task;
	struct UI_stack_item *link;
};

typedef struct UI_task UI_task;
typedef struct UI_stack_item UI_stack_item;

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

/*
	Создание новой задачи
*/
UI_task * UI_new_task(UI_surface *surf, void (* draw)(), void (* press_up)(), void (* press_down)(), void (* press_enter)());

/*
	Затолкать задачу
*/
void UI_push_task(UI_task *task);

/*
	Достать задачу
*/
UI_task * UI_pop_task();

#endif