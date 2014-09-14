#include "../UI.h"

ScreenInfo *MenuScreen;

void UI_init(ScreenInfo *screen, CKF_Font *font){
	menu_init(UI_surf_init(screen->width - 80, screen->height - 80), font);
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
	UI_draw_surf(menu_redraw(), 40, 40);
}

void UI_clear_src(){
	memset(MenuScreen->buffer, 0, MenuScreen->len_byte);
}