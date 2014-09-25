#include "../UI_menu.h"
#include "../UI_tree.h"
#include <stdio.h>

struct { //Структура содержит в себе текущее состяние меню
	CKF_MenuList	*cur_menu_list;		//Указатель на текущий массив пунктов меню
	CKF_Font		*font;				//Шрифт используемый в menu_draw()
	CKF_MenuItem	*first_item;		//Первый пункт попадающий на эктан
	CKF_MenuItem	*cur_item;			//Текущий пункт

	unsigned int	n_first_imem;		//Номер первого пункта попадающего на экран
	unsigned int	n_cur_item;			//Номер текушего пункта
	unsigned int	max_lines;

	CKF_MenuItem	*last_first_item;	//Последний пункт, который может быть первым
}MenuState;

UI_surface *MenuSurface;

void menu_init(UI_surface *surf, CKF_Font *font){
	#ifdef DEBUG
	printf("In menu_init()\n");
	#endif

	MenuSurface = surf;

	MenuState.cur_menu_list	= init_menu_tree();
	MenuState.font			= font;
	MenuState.first_item	= MenuState.cur_menu_list->vertex;
	MenuState.cur_item		= MenuState.cur_menu_list->vertex;

	MenuState.n_first_imem	= 0;
	MenuState.n_cur_item	= 0;
	MenuState.max_lines		= MenuSurface->height / MenuState.font->height;

	if(MenuState.cur_menu_list->count > MenuState.max_lines){
		int i;
		MenuState.last_first_item = MenuState.cur_menu_list->edge;
		for(i = 0; i < MenuState.max_lines - 1; i++){
			MenuState.last_first_item = MenuState.last_first_item->prev;
		}
	}
	else{
		MenuState.last_first_item = MenuState.cur_menu_list->vertex;
	}
}

void menu_draw(){
	#ifdef DEBUG
	printf("In menu_draw()\n");
	#endif

	int i, max_i;
	CKF_MenuItem *i_item;

	i = 0;
	max_i = MenuState.max_lines;
	i_item = MenuState.first_item;
	//TODO: oprimization
	while(i_item && i < max_i){
		if(MenuState.cur_item == i_item) draw_char(MenuSurface, MenuState.font, '>', 0, i * MenuState.font->height);
		draw_string(MenuSurface, MenuState.font, i_item->str, MenuState.font->width, i * MenuState.font->height);

		i++;
		i_item = i_item->next;
	}

	UI_border(MenuSurface);
}

void menu_up(){
	#ifdef DEBUG
	printf("In menu_up()\n");
	#endif

	if(MenuState.cur_item->prev){
		MenuState.cur_item = MenuState.cur_item->prev;
		MenuState.n_cur_item--;

		if(MenuState.n_cur_item <= MenuState.n_first_imem && MenuState.n_cur_item > 0){
			MenuState.n_first_imem--;
			MenuState.first_item = MenuState.first_item->prev;
		}
	}
	else{
		MenuState.cur_item		= MenuState.cur_menu_list->edge;
		MenuState.n_cur_item	= MenuState.cur_menu_list-> count - 1;
		MenuState.first_item	= MenuState.last_first_item;
		MenuState.n_first_imem	= MenuState.max_lines < MenuState.cur_menu_list->count?
			MenuState.cur_menu_list-> count - MenuState.max_lines:
			0;
	}

	#ifdef DEBUG
	printf("MenuState.n_cur_item:%d, MenuState.n_first_imem: %d\n", MenuState.n_cur_item, MenuState.n_first_imem);
	#endif
}

void menu_down(){
	#ifdef DEBUG
	printf("In menu_down()\n");
	#endif

	if(MenuState.cur_item->next){
		MenuState.cur_item = MenuState.cur_item->next;
		MenuState.n_cur_item++;

		if(MenuState.n_cur_item >= MenuState.n_first_imem + MenuState.max_lines - 1 && MenuState.n_cur_item < MenuState.cur_menu_list->count - 1){
			MenuState.n_first_imem++;
			MenuState.first_item = MenuState.first_item->next;
		}
	}
	else{
		MenuState.cur_item		= MenuState.cur_menu_list->vertex;
		MenuState.n_cur_item	= 0;
		MenuState.first_item	= MenuState.cur_menu_list->vertex;
		MenuState.n_first_imem	= 0;
	}

	#ifdef DEBUG
	printf("MenuState.n_cur_item:%d, MenuState.n_first_imem: %d\n", MenuState.n_cur_item, MenuState.n_first_imem);
	#endif
}

void menu_enter(){
	#ifdef DEBUG
	printf("In menu_enter()\n");
	#endif

	if(MenuState.cur_item->call_back){
		MenuState.cur_item->call_back();
	}
	else{
		MenuState.cur_menu_list	= MenuState.cur_item->child;

		MenuState.first_item	= MenuState.cur_menu_list->vertex;
		MenuState.cur_item		= MenuState.cur_menu_list->vertex;

		MenuState.n_first_imem	= 0;
		MenuState.n_cur_item	= 0;

		if(MenuState.cur_menu_list->count > MenuState.max_lines){
			int i;
			MenuState.last_first_item = MenuState.cur_menu_list->edge;
			for(i = 0; i < MenuState.max_lines - 1; i++){
				MenuState.last_first_item = MenuState.last_first_item->prev;
			}
		}
		else{
			MenuState.last_first_item = MenuState.cur_menu_list->vertex;
		}
	}
}

UI_control_funcs * menu_get_control_funcs(){
	UI_control_funcs *funcs;
	funcs = malloc(sizeof(UI_control_funcs));

	funcs->draw			= menu_draw;
	funcs->press_up		= menu_up;
	funcs->press_down	= menu_down;
	funcs->press_enter	= menu_enter;

	return funcs;
}

CKF_Font * menu_get_font(){
	return MenuState.font;
}