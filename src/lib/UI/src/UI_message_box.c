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
const char	*MainString;

void message_draw(){
	UI_border(MainSurface);
	draw_string(MainSurface, MainFont, MainString, 1, 0);
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

void UI_show_message(const char *str){
	UI_task				*task;
	UI_control_funcs	*funcs;

	funcs = message_ctrl_funcs();

	MainSurface	= UI_surf_init(150, 100);
	MainFont	= menu_get_font();
	MainString	= str;
	task		= UI_new_task(MainSurface, message_ctrl_funcs());

	free(funcs);

	UI_push_task(task);
}