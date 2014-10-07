#include "../UI.h"
#include <stdlib.h>

ScreenInfo *MenuScreen;

void UI_init(ScreenInfo *screen, CKF_Font *font){
	UI_surface			*menu_surf;
	UI_task				*menu_task;
	UI_control_funcs	*ctrl_fs;

	menu_surf	= UI_surf_init(screen->width - 80, screen->height - 100);
	ctrl_fs		= menu_get_control_funcs();

	UI_task_init();
	menu_init(menu_surf, font);

	menu_task = UI_new_task(menu_surf, ctrl_fs);
	UI_push_task(menu_task);

	free(ctrl_fs);

	MenuScreen = screen;
}

void UI_up(){
	if(UI_get_task()->press_up != NULL)
		UI_get_task()->press_up();
}

void UI_down(){
	if(UI_get_task()->press_down != NULL)
		UI_get_task()->press_down();
}

void UI_enter(){
	if(UI_get_task()->press_enter != NULL)
		UI_get_task()->press_enter();
}

void UI_draw(){
	UI_task *local_stack_item = UI_get_task();

	UI_clear_surf(local_stack_item->surf);
	local_stack_item->draw();
	UI_draw_surf(local_stack_item->surf,
		(MenuScreen->width - local_stack_item->surf->width) / 2,
		(MenuScreen->height - local_stack_item->surf->height) / 2);
}

void UI_clear_src(){
	memset(MenuScreen->buffer, 0, MenuScreen->len_byte);
}