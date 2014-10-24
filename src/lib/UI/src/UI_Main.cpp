#include "../UI_Main.h"

#include <iostream>
#include <cassert>

#define DEBUG_UI_MAIN

UI::UI(ScreenInfo &scr, Font &font): default_font(font){
	assert(scr.width % 8 == 0);

	width			= scr.width;
	height			= scr.height;
	buf_size		= scr.len_byte;
	buffer			= (unsigned char *) scr.buffer;

	surf_is_my		= false;

	my_state		= changed;
	need_refresh	= true;
}

UI::~UI(){
	#ifdef DEBUG_UI_MAIN
	std::cout << "IN UI::~UI()" << std::endl;
	#endif

	for(Task *task; !empty(); pop()){
		delete top();
	}
}

void UI::push(Task *task){
	#ifdef DEBUG_UI_MAIN
	std::cout << "NEED REFRESH" << std::endl;
	#endif

	need_refresh = true;
	std::stack<Task*>::push(task);
}


void UI::pop(){
	#ifdef DEBUG_UI_MAIN
	std::cout << "NEED REFRESH" << std::endl;
	#endif

	need_refresh = true;
	std::stack<Task*>::pop();
}

void UI::up(){
	if(top()->up()) need_refresh = true;
}

void UI::down(){
	if(top()->down()) need_refresh = true;

}

void UI::select(){
	if(top()->select()) need_refresh = true;

}

void UI::draw(){
	if(need_refresh){
		my_state = busy;

		#ifdef DEBUG_UI_MAIN
		std::cout << "state: BUSY" << std::endl;
		#endif
		
		clear();

		Surface &surf = top()->draw();
		Surface::draw(surf);

		my_state = changed;

		#ifdef DEBUG_UI_MAIN
		std::cout << "state: CHANGED" << std::endl;
		#endif

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