#include "../UI.h"
#include <stdlib.h>

ScreenInfo *MenuScreen;

void UI_init(ScreenInfo *screen, CKF_Font *font){
	UI_surface			*menu_surf;
	UI_task				*menu_task;
	UI_control_funcs	*ctrl_fs;

	menu_surf	= UI_surf_init(screen->width - 40, screen->height - 80);
	ctrl_fs		= menu_get_control_funcs();

	UI_task_init();
	menu_init(menu_surf, font);

	menu_task = UI_new_task(menu_surf, NULL, ctrl_fs);
	UI_push_task(menu_task);

	free(ctrl_fs);

	MenuScreen = screen;
}

void UI_up(){
	UI_task *local_task = UI_get_task();

	if(local_task->press_up != NULL)
		local_task->press_up(local_task->data);
}

void UI_down(){
	UI_task *local_task = UI_get_task();

	if(local_task->press_down != NULL)
		local_task->press_down(local_task->data);
}

void UI_enter(){
	UI_task *local_task = UI_get_task();

	if(local_task->press_enter != NULL)
		local_task->press_enter(local_task->data);
}

void UI_draw(){
	UI_task *local_stack_item = UI_get_task();

	UI_clear_surf(local_stack_item->surf);
	local_stack_item->draw(local_stack_item->data);
	UI_draw_surf(local_stack_item->surf,
		(MenuScreen->width - local_stack_item->surf->width) / 2,
		(MenuScreen->height - local_stack_item->surf->height) / 2);
}

void UI_clear_src(){
	memset(MenuScreen->buffer, 0, MenuScreen->len_byte);
}