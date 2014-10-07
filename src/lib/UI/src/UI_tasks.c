#include "../UI_tasks.h"
#include <stdlib.h>

UI_stack_item *StackTop;

void UI_task_init(){
	StackTop = NULL;
}

UI_task * UI_new_task(UI_surface *surf, void *data, UI_control_funcs *funcs){
	UI_task *task;

	task = malloc(sizeof(UI_task));

	task->surf			= surf;
	task->data			= data;
	task->draw			= funcs->draw;
	task->press_up		= funcs->press_up;
	task->press_down	= funcs->press_down;
	task->press_enter	= funcs->press_enter;

	return task;
}

void UI_push_task(UI_task *task){
	UI_stack_item *new_top_task;

	new_top_task		= malloc(sizeof(UI_stack_item));
	new_top_task->task	= task;
	new_top_task->link	= StackTop;

	StackTop			= new_top_task;
}

UI_task * UI_pop_task(){
	UI_stack_item *old_top;
	UI_task *task;

	old_top	= StackTop;
	task	= StackTop->task;

	StackTop = StackTop->link;

	free(old_top);

	return task;
}

UI_task * UI_get_task(){
	return StackTop->task;
}
