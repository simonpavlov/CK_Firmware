#include "../UI_Main.h"
#include <iostream>

UI::UI(ScreenInfo &scr, Font &font): my_screen(* new Surface(scr)), my_font(font) {}

UI::~UI() {
	std::cout << "IN UI::~UI()" << std::endl;

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
	my_screen.draw(surf, (my_screen.get_width() - surf.get_width()) / 2, (my_screen.get_height() - surf.get_height()) / 2);
}

void UI::clear_scr(){
	std::cout << "IN UI::clear_scr()" << std::endl;
	my_screen.clear();
}
