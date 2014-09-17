#include "../UI.h"
#include <stdlib.h>

struct{
	UI_stack_item *stack_top;
} UI_State;

ScreenInfo *MenuScreen;

void UI_init(ScreenInfo *screen, CKF_Font *font){
	UI_State.stack_top = NULL;

	UI_surface *menu_surf;
	UI_task *menu_task;

	menu_surf = UI_surf_init(screen->width - 80, screen->height - 80);
	menu_task = UI_new_task(menu_surf, menu_draw, menu_up, menu_down, menu_enter);
	UI_push_task(menu_task);

	menu_init(menu_surf, font);

	MenuScreen = screen;
}

void UI_up(){
	UI_State.stack_top->task->press_up();
}

void UI_down(){
	UI_State.stack_top->task->press_down();
}

void UI_enter(){
	UI_State.stack_top->task->press_enter();
}

void UI_draw(){
	UI_clear_surf(UI_State.stack_top->task->surf);
	UI_State.stack_top->task->draw();
	UI_draw_surf(UI_State.stack_top->task->surf, 40, 40);
}

void UI_clear_src(){
	memset(MenuScreen->buffer, 0, MenuScreen->len_byte);
}

UI_task * UI_new_task(UI_surface *surf, void (* draw)(), void (* press_up)(), void (* press_down)(), void (* press_enter)()){
	UI_task *task;

	task = malloc(sizeof(UI_task));

	task->surf			= surf;
	task->draw			= draw;
	task->press_up		= press_up;
	task->press_down	= press_down;
	task->press_enter	= press_enter;

	return task;
}

void UI_push_task(UI_task *task){
	UI_stack_item *new_top_task;

	new_top_task		= malloc(sizeof(UI_stack_item));
	new_top_task->task	= task;
	new_top_task->link	= UI_State.stack_top;

	UI_State.stack_top	= new_top_task;
}

UI_task * UI_pop_task(){
	UI_stack_item *old_top;
	UI_task *task;

	old_top	= UI_State.stack_top;
	task	= UI_State.stack_top->task;

	UI_State.stack_top = UI_State.stack_top->link;

	free(old_top);

	return task;
}
