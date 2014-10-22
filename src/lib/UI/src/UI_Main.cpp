#include "../UI_Main.h"
#include <iostream>

UI::UI(ScreenInfo &scr, Font &font): my_screen(* new Surface(scr)), my_font(font){}

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
	my_screen.draw(surf);
}

void UI::clear_scr(){
	#ifdef DEBUG_UI_MAIN
	std::cout << "IN UI::clear_scr()" << std::endl;
	#endif

	my_screen.clear();
}
