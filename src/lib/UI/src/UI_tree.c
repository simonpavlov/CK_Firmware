#include "../UI_tree.h"
#include <stdio.h>
#include <stdlib.h>

CKF_MenuList * init_menu_tree(){
	#ifdef DEBUG
	printf("Initialization menu tree.\n");
	#endif

	CKF_MenuList *list;
	list = (CKF_MenuList *) malloc(sizeof(CKF_MenuList));

	list->edge	= NULL;
	list->count	= 0;

	#include <menu.md.h>

	return list;
}

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