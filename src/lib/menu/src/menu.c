#include "../menu.h"
#include "../menu_tree.h"
#include <stdio.h>
#include <stdlib.h>

struct { //Структура содержит в себе текущее состяние меню
	CKF_MenuList	*cur_menu_list;		//Указатель на текущий массив пунктов меню
	CKF_Font		*font;				//Шрифт используемый в menu_draw()
	CKF_MenuItem	*first_item;		//Первый пункт попадающий на эктан
	CKF_MenuItem	*cur_item;			//Текущий пункт

	unsigned int	top_margin;			//Отступ сверху

	unsigned int	n_first_imem;		//Номер первого пункта попадающего на экран
	unsigned int	n_cur_item;			//Номер текушего пункта
	unsigned int	max_lines;

	CKF_MenuItem	*last_first_item;	//Последний пункт, который может быть первым
}MenuState;

ScreenInfo *MenuScreen;

void add_item(CKF_MenuList *list, char *str, void (*call_back)()){
	#ifdef DEBUG
	printf("In add_item()\n");
	#endif

	CKF_MenuItem *item;
	item = (CKF_MenuItem *) malloc(sizeof(CKF_MenuItem));

	item->prev = list->edge;
	item->next = NULL;

	item->str = str;
	item->call_back = call_back;
	item->child = NULL;

	if(list->edge) list->edge->next = item;
	else list->vertex = item;

	list->edge = item;

	list->count++;
}

void del_item(CKF_MenuList *list, CKF_MenuItem *item){
}

void add_list(CKF_MenuList *list, CKF_MenuItem *item){
	#ifdef DEBUG
	printf("In add_list()\n");
	#endif

	CKF_MenuList *new_list;

	new_list = (CKF_MenuList *) malloc(sizeof(CKF_MenuList));

	new_list->parent	= list;
	new_list->vertex	= NULL;
	new_list->edge		= NULL;
	new_list->count		= 0;

	item->child			= new_list;
}

void menu_init(ScreenInfo *screen, CKF_Font *font){
	#ifdef DEBUG
	printf("In menu_init()\n");
	#endif

	MenuScreen = screen;

	MenuState.cur_menu_list	= init_menu_tree();
	MenuState.font			= font;
	MenuState.first_item	= MenuState.cur_menu_list->vertex;
	MenuState.cur_item		= MenuState.cur_menu_list->vertex;

	MenuState.top_margin	= 20; //Отступ для бара

	MenuState.n_first_imem	= 0;
	MenuState.n_cur_item	= 0;
	MenuState.max_lines		= (MenuScreen->height - MenuState.top_margin) / MenuState.font->height;

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
	while(i_item && i <= max_i){
		if(MenuState.cur_item == i_item) draw_char(MenuState.font, '>', 0, MenuState.top_margin + (i * MenuState.font->height));
		draw_string(MenuState.font, i_item->str, MenuState.font->width, MenuState.top_margin + (i * MenuState.font->height));

		i++;
		i_item = i_item->next;
	}
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

void clear_src(){
	int i;
	for(i = 0; i < MenuScreen->len_byte; i++){
		*(MenuScreen->buffer + i) = 0;
	}
}