#include "../menu_tree.h"

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
