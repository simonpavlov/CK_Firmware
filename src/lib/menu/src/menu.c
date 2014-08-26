#include "../menu.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct{
	char *name;
	void (*call_back)();
}CKF_MenuItem;

typedef struct{
	CKF_MenuItem *menu_items;
	int count;
}CKF_MenuList;

struct {
	CKF_MenuList	cur_menu_list;	//Указатель на текущий массив пунктов меню
	CKF_Font		*menu_font;		//Шрифт используемый в menu_draw()
	int 			n_first_item;	//Номер первого отрисованного пункта
	int				n_cur_item;		//Номер текущего пункта
}CKF_MenuState;


ScreenInfo *MenuScreen;

void change_cur_menu_list(){
	#ifdef DEBUG
	printf("In change_cur_menu_list()\n");
	#endif
}

void menu_init(ScreenInfo *screen, CKF_Font *font){
	MenuScreen = screen;
	CKF_MenuState.menu_font = font;

	//TODO: Инициализация меню хромает.

	CKF_MenuState.cur_menu_list.menu_items = (CKF_MenuItem *) malloc(sizeof(CKF_MenuItem) * 12);
	CKF_MenuState.cur_menu_list.count = 12;

	CKF_MenuState.cur_menu_list.menu_items[ 0] = (CKF_MenuItem) {"A captive, alone in a dungeon I dwell,", change_cur_menu_list};
	CKF_MenuState.cur_menu_list.menu_items[ 1] = (CKF_MenuItem) {"Entombed in the stillness and murk of a cell.", change_cur_menu_list};
	CKF_MenuState.cur_menu_list.menu_items[ 2] = (CKF_MenuItem) {"Outside, in the courtyard, in wild, frenzied play,", change_cur_menu_list};
	CKF_MenuState.cur_menu_list.menu_items[ 3] = (CKF_MenuItem) {"My comrade, an eagle, has pounced on his prey.", change_cur_menu_list};
	CKF_MenuState.cur_menu_list.menu_items[ 4] = (CKF_MenuItem) {"Then, leaving the blood-spattered morsel, his eye,", change_cur_menu_list};
	CKF_MenuState.cur_menu_list.menu_items[ 5] = (CKF_MenuItem) {"He fixes on me with a dolorous cry,", change_cur_menu_list};
	CKF_MenuState.cur_menu_list.menu_items[ 6] = (CKF_MenuItem) {"A cry that is more like a call or a plea-", change_cur_menu_list};
	CKF_MenuState.cur_menu_list.menu_items[ 7] = (CKF_MenuItem) {"\"'Tis time,\" he is saying, \"'tis time, let us flee!", change_cur_menu_list};
	CKF_MenuState.cur_menu_list.menu_items[ 8] = (CKF_MenuItem) {"\"We're both wed to freedom, so let us away", change_cur_menu_list};
	CKF_MenuState.cur_menu_list.menu_items[ 9] = (CKF_MenuItem) {"To where lonely storm-clouds courageously stray,", change_cur_menu_list};
	CKF_MenuState.cur_menu_list.menu_items[10] = (CKF_MenuItem) {"Where turbulent seas rush to merge with the sky,", change_cur_menu_list};
	CKF_MenuState.cur_menu_list.menu_items[11] = (CKF_MenuItem) {"Where only the winds dare to venture and I!...\"", change_cur_menu_list};

	CKF_MenuState.n_first_item	= 0;
	CKF_MenuState.n_cur_item	= 0;
}

void menu_draw(){
	#ifdef DEBUG
	printf("In menu_draw()\n");
	#endif

	int i, max_i;
	//TODO: подсчёт максимального количества строк.
	max_i = CKF_MenuState.cur_menu_list.count;
	for(i = 0; i < max_i; i++){
		#ifdef DEBUG
		printf("Trying draw %dth item.\n", i);
		#endif

		//TODO: обработка места для бара
		if(i == CKF_MenuState.n_cur_item) draw_char(CKF_MenuState.menu_font, '>', 0, i * CKF_MenuState.menu_font->height);
		draw_string(CKF_MenuState.menu_font, CKF_MenuState.cur_menu_list.menu_items[i + CKF_MenuState.n_first_item].name, CKF_MenuState.menu_font->width, i * CKF_MenuState.menu_font->height);
	}
}

void menu_up(){
	#ifdef DEBUG
	printf("In menu_up()\n");
	#endif

	CKF_MenuState.n_cur_item = (CKF_MenuState.n_cur_item + (CKF_MenuState.cur_menu_list.count - 1)) % (CKF_MenuState.cur_menu_list.count);
}

void menu_down(){
	#ifdef DEBUG
	printf("In menu_down()\n");
	#endif

	CKF_MenuState.n_cur_item = (CKF_MenuState.n_cur_item + 1) % (CKF_MenuState.cur_menu_list.count);
}

void menu_enter(){
	#ifdef DEBUG
	printf("In menu_enter()\n");
	#endif

	CKF_MenuState.cur_menu_list.menu_items[CKF_MenuState.n_cur_item].call_back();
}

void clear_src(){
	int i;
	for(i = 0; i < MenuScreen->len_byte; i++){
		*(MenuScreen->buffer + i) = 0;
	}
}