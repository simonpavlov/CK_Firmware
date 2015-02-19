#include "../UI_Main.h"

#include <iostream>
#include <cassert>

#define DEBUG_UI_MAIN

UI::UI(Font font): default_font(font){
	#ifdef DEBUG_UI_MAIN
	std::cout << "IN UI::UI()" << std::endl;
	#endif

	set_screen_res(320, 240);
	emul_init(VIDEO_SYS);

	ScreenInfo scr = *get_screen_info();
	assert(scr.width % 8 == 0);

	width			= scr.width;
	height			= scr.height;
	buf_size		= scr.len_byte;
	buffer			= (unsigned char *) scr.buffer;

	surf_is_my		= false;

	need_refresh	= false;
}

UI::~UI(){
	#ifdef DEBUG_UI_MAIN
	std::cout << "IN UI::~UI()" << std::endl;
	#endif

	for(; !empty(); pop());
	emul_quit(VIDEO_SYS);
}

void UI::push(Task *task){
	std::stack<Task*>::push(task);

	#ifdef DEBUG_UI_MAIN
	std::cout << "NEED REFRESH" << std::endl;
	#endif

	need_refresh = true;
}


void UI::pop(){
	delete this->top();
	std::stack<Task*>::pop();

	if(!empty()){
		#ifdef DEBUG_UI_MAIN
		std::cout << "NEED REFRESH" << std::endl;
		#endif

		need_refresh = true;
	}
}

void UI::up(){
	if(top()->up()) need_refresh = true;
}

void UI::down(){
	if(top()->down()) need_refresh = true;

}

void UI::select(){
	Task::result res;

	res = top()->select();

	if(res == Task::surf_changed) need_refresh = true;
	else if(res == Task::complite) UI::pop();
}

void UI::back(){
	if(top()->back()) need_refresh = true;
}

void UI::draw(){
	if(empty()) return;

	if(need_refresh){
		clear();

		Surface &surf = top()->draw();
		Surface::draw(surf);

		refresh_video_buffer();

		need_refresh = false;
	}
}

/*
void UI::clear_scr(){
	#ifdef DEBUG_UI_MAIN
	std::cout << "IN UI::clear_scr()" << std::endl;
	#endif

	clear();
}
*/
