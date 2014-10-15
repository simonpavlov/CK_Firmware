#include "../UI_Main.h"
#include <iostream>

UI::UI(ScreenInfo &scr): my_screen(Surface(scr)) {
}

UI::~UI() {
	for(Task *task; !empty(); pop()){
		std::cout << "IN UI::~UI()" << std::endl;
		task = top();
		delete task;
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
