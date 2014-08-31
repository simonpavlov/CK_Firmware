#ifndef CKF_MENU
#define CKF_MENU

#include "font.h"
#include <emul/emulator.h>

/*
Отдельный пункт меню
*/
struct CKF_MenuItem{
	struct CKF_MenuItem *prev;
	struct CKF_MenuItem *next;

	char				*str;
	void				(*call_back)();
	struct CKF_MenuList	*child;
};

/*
Лист меню
*/
struct CKF_MenuList{
	struct CKF_MenuList *parent;

	struct CKF_MenuItem *vertex;
	struct CKF_MenuItem *edge;
	int count;
};

typedef struct CKF_MenuItem CKF_MenuItem;
typedef struct CKF_MenuList CKF_MenuList;

/*
Добавление путкта меню
*/
void add_item(CKF_MenuList *list, char *str, void (*call_back)());

/*
Удаление пункта меню item из листа list
*/
void del_item(CKF_MenuList *list, CKF_MenuItem *item);

/*
Создаёт новы пустой лист меню и привязывает его к item, list счиаепся родителем
*/
void add_list(CKF_MenuList *list, CKF_MenuItem *item);

/*
Инициализация меню
*/
void menu_init(ScreenInfo *screen, CKF_Font *font);

/*
Отрисовка меню
*/
void menu_draw();

/*
Перемещение курсора на один пункт вверх
*/
void menu_up();

/*
Перемещение курсора на один пункт вниз
*/
void menu_down();

/*
Выбрать текущий пункт
*/
void menu_enter();

/*
Очищает видео буфер
*/
void clear_scr();

#endif
