#include "../UI_callback.h"
#include "../UI_surface.h"
#include "../UI_tasks.h"
#include "../UI_control_funcs.h"
#include "../UI_menu.h"
#include <stdio.h>
#include <stdlib.h>

UI_surface *TestSurf;

void test_draw(){
	UI_border(TestSurf);
}

void test_exit(){
	UI_pop_task();
}

UI_control_funcs * get_ctrl_funcs(){
	UI_control_funcs *funcs = malloc(sizeof(UI_control_funcs));

	funcs->draw			= test_draw;
	funcs->press_up		= test_exit;
	funcs->press_down	= test_exit;
	funcs->press_enter	= test_exit;

	return funcs;
}

void test_callback(){
	printf("IN TEST_CALLBACK\n");

	UI_task		*task;

	TestSurf = UI_surf_init(10, 10);
	task = UI_new_task(TestSurf, get_ctrl_funcs());

	UI_push_task(task);
}