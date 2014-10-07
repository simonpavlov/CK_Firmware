#include "../UI_message_box.h"

#include "../UI_control_funcs.h"
#include "../UI_surface.h"
#include "../UI_tasks.h"
#include "../UI_font.h"
#include "../UI_menu.h"

#include <stdlib.h>
#include <stdio.h>

UI_surface	*MainSurface;
CKF_Font	*MainFont;

void message_draw(const char *str){
	UI_border(MainSurface);
	draw_string(MainSurface, MainFont, str, 1, 0);
}

void message_exit(){
	//TODO: deleting
	UI_pop_task();
}

UI_control_funcs * message_ctrl_funcs(){
	UI_control_funcs *funcs = malloc(sizeof(UI_control_funcs));

	funcs->draw			= message_draw;
	funcs->press_up		= NULL;
	funcs->press_down	= NULL;
	funcs->press_enter	= message_exit;

	return funcs;
}

void UI_show_message(char *str){
	UI_task				*task;
	UI_control_funcs	*funcs;
	char				*message_string = str;

	funcs = message_ctrl_funcs();

	MainSurface	= UI_surf_init(150, 100);
	MainFont	= menu_get_font();
	task		= UI_new_task(MainSurface, message_string, message_ctrl_funcs());

	free(funcs);

	UI_push_task(task);
}