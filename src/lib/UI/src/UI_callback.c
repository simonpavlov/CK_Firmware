#include "../UI_callback.h"

#include "../UI_surface.h"
#include "../UI_tasks.h"
#include "../UI_control_funcs.h"
#include "../UI_message_box.h"
#include <stdlib.h>
#include <stdio.h>

UI_surface *TestSurf;

void test_draw(){
	UI_border(TestSurf);
}

void test_up(void *data){
	printf("Data: %d\n", *(int *)data);
	(*(int *)data)++;
}

void test_down(void *data){
	printf("Data: %d\n", *(int *)data);
	(*(int *)data)--;
}

void test_exit(){
	//TODO: deleting
	UI_pop_task();
}

UI_control_funcs * get_ctrl_funcs(){
	UI_control_funcs *funcs = malloc(sizeof(UI_control_funcs));

	funcs->draw			= test_draw;
	funcs->press_up		= test_up;
	funcs->press_down	= test_down;
	funcs->press_enter	= test_exit;

	return funcs;
}

void test_callback(){
	printf("IN TEST_CALLBACK\n");

	UI_task				*task;
	UI_control_funcs	*funcs;
	int					*data;

	data = malloc(sizeof(int));
	*data = 0;

	funcs = get_ctrl_funcs();

	TestSurf = UI_surf_init(10, 10);
	task = UI_new_task(TestSurf, data, funcs);

	free(funcs);

	UI_push_task(task);
}

void show_HELLO_BOX(){
	UI_show_message("HELLO_BOX");
}