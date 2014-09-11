#ifndef UI_TREE
#define UI_TREE

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
Создаёт дерево меню
*/
CKF_MenuList * init_menu_tree();

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

#endif