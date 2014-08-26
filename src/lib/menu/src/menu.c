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

CKF_MenuList	CurMenuList;	//Указатель на текущий массив пунктов меню
CKF_Font		*MenuFont;		//Шрифт используемый в menu_draw()
int 			nFirstItem;		//Номер первого отрисованного пункта
int				nCurItem;		//Номер текущего пункта

char	*VideoBuffer;	//Ссылка на видео буфер
int		ScreenWidth;	//Ширина дисплея
int 	ScreenHeight;	//Высота дисплея

void change_cur_menu_list(){
	#ifdef DEBUG
	printf("In change_cur_menu_list()\n");
	#endif
}

void menu_init(char *video_buffer, int width, int height, CKF_Font *font){
	VideoBuffer =	video_buffer;
	ScreenWidth =	width;
	ScreenHeight =	height;

	MenuFont = font;

	//TODO: Инициализация меню хромает.

	CurMenuList.menu_items = (CKF_MenuItem *) malloc(sizeof(CKF_MenuItem) * 12);
	CurMenuList.count = 12;

	CurMenuList.menu_items[ 0] = (CKF_MenuItem) {"A captive, alone in a dungeon I dwell,", change_cur_menu_list};
	CurMenuList.menu_items[ 1] = (CKF_MenuItem) {"Entombed in the stillness and murk of a cell.", change_cur_menu_list};
	CurMenuList.menu_items[ 2] = (CKF_MenuItem) {"Outside, in the courtyard, in wild, frenzied play,", change_cur_menu_list};
	CurMenuList.menu_items[ 3] = (CKF_MenuItem) {"My comrade, an eagle, has pounced on his prey.", change_cur_menu_list};
	CurMenuList.menu_items[ 4] = (CKF_MenuItem) {"Then, leaving the blood-spattered morsel, his eye,", change_cur_menu_list};
	CurMenuList.menu_items[ 5] = (CKF_MenuItem) {"He fixes on me with a dolorous cry,", change_cur_menu_list};
	CurMenuList.menu_items[ 6] = (CKF_MenuItem) {"A cry that is more like a call or a plea-", change_cur_menu_list};
	CurMenuList.menu_items[ 7] = (CKF_MenuItem) {"\"'Tis time,\" he is saying, \"'tis time, let us flee!", change_cur_menu_list};
	CurMenuList.menu_items[ 8] = (CKF_MenuItem) {"\"We're both wed to freedom, so let us away", change_cur_menu_list};
	CurMenuList.menu_items[ 9] = (CKF_MenuItem) {"To where lonely storm-clouds courageously stray,", change_cur_menu_list};
	CurMenuList.menu_items[10] = (CKF_MenuItem) {"Where turbulent seas rush to merge with the sky,", change_cur_menu_list};
	CurMenuList.menu_items[11] = (CKF_MenuItem) {"Where only the winds dare to venture and I!...\"", change_cur_menu_list};

	nFirstItem	= 0;
	nCurItem	= 0;
}

void menu_draw(){
	#ifdef DEBUG
	printf("In menu_draw()\n");
	#endif

	int i, max_i;
	//TODO: подсчёт максимального количества строк.
	max_i = CurMenuList.count;
	for(i = 0; i < max_i; i++){
		#ifdef DEBUG
		printf("Trying draw %dth item.\n", i);
		#endif

		//TODO: обработка места для бара
		if(i == nCurItem) draw_char(MenuFont, '>', 0, i * MenuFont->height);
		draw_string(MenuFont, CurMenuList.menu_items[i + nFirstItem].name, MenuFont->width, i * MenuFont->height);
	}
}

void menu_up(){
	#ifdef DEBUG
	printf("In menu_up()\n");
	#endif

	nCurItem = (nCurItem + (CurMenuList.count - 1)) % (CurMenuList.count);
}

void menu_down(){
	#ifdef DEBUG
	printf("In menu_down()\n");
	#endif

	nCurItem = (nCurItem + 1) % (CurMenuList.count);
}

void menu_enter(){
	#ifdef DEBUG
	printf("In menu_enter()\n");
	#endif

	CurMenuList.menu_items[nCurItem].call_back();
}

void clear_src(){
	int i;
	for(i = 0; i < ((ScreenHeight * ScreenWidth) + 7) / 8; i++){
		*(VideoBuffer + i) = 0;
	}
}