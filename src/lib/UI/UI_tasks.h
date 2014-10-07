#ifndef UI_TASKS
#define UI_TASKS

#include "UI_surface.h"
#include "UI_control_funcs.h"

/*
	Отдельная задача, под задачей понимается: меню и различные
	всплывающий окна.
*/
struct UI_task{
	UI_surface *surf;
	void *data;
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

typedef struct UI_task			UI_task;
typedef struct UI_stack_item	UI_stack_item;

/*
	Итициализация стека задач
*/
void UI_task_init();

/*
	Создание новой задачи
*/
UI_task * UI_new_task(UI_surface *surf, void *data, UI_control_funcs *funcs);

/*
	Затолкать задачу
*/
void UI_push_task(UI_task *task);

/*
	Достать задачу
*/
UI_task * UI_pop_task();

/*
	Возвпащает ссылку на верхнюю задчу не извлекая её
*/
UI_task * UI_get_task();

#endif