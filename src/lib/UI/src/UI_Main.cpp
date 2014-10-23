#include "../UI_Main.h"

#include <iostream>
#include <cassert>

UI::UI(ScreenInfo &scr, Font &font): default_font(font){
	assert(scr.width % 8 == 0);

	width		= scr.width;
	height		= scr.height;
	buf_size	= scr.len_byte;
	buffer		= (unsigned char *) scr.buffer;

	my_state	= changed;
	surf_is_my	= false;
}

UI::~UI(){
	#ifdef DEBUG_UI_MAIN
	std::cout << "IN UI::~UI()" << std::endl;
	#endif

	for(Task *task; !empty(); pop()){
		delete top();
	}
}

void UI::up(){
	top()->up();
}

void UI::down(){
	top()->down();

}

void UI::select(){
	top()->select();

}

void UI::draw(){
	Surface &surf = top()->draw();

	my_state = busy;
	Surface::draw(surf);
	my_state = changed;
}

/*
void UI::clear_scr(){
	#ifdef DEBUG_UI_MAIN
	std::cout << "IN UI::clear_scr()" << std::endl;
	#endif

	clear();
}
*/