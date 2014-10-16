#include "../UI_Main.h"
#include <iostream>

UI::UI(ScreenInfo &scr): my_screen(Surface(scr)) {}

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
	top()->draw();

}

void UI::clear_scr(){

}
