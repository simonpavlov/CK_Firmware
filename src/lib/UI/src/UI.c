#include "../UI.h"

ScreenInfo *MenuScreen;

void UI_init(ScreenInfo *screen, CKF_Font *font){
	menu_init(screen, font);
	MenuScreen = screen;
}

void UI_up(){
	menu_up();
}

void UI_down(){
	menu_down();
}

void UI_enter(){
	menu_enter();
}

void UI_draw(){
	menu_draw();
}

void UI_clear_src(){
	int i;
	for(i = 0; i < MenuScreen->len_byte; i++){
		*(MenuScreen->buffer + i) = 0;
	}
}