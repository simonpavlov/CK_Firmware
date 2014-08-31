#include "../menu_tree.h"

CKF_MenuList * init_menu_tree(){
	#ifdef DEBUG
	printf("Initialization menu tree.\n");
	#endif

	CKF_MenuList *root_list, *list;
	root_list = (CKF_MenuList *) malloc(sizeof(CKF_MenuList));

	root_list->edge		= NULL;
	root_list->count	= 0;

	add_item(root_list, "fitst item.", NULL);
	add_item(root_list, " 1-st item.", NULL);
	add_item(root_list, " 2-st item.", NULL);
	add_item(root_list, " 3-st item.", NULL);
	add_item(root_list, " 4-st item.", NULL);
	add_item(root_list, " 5-st item.", NULL);
	add_item(root_list, " 6-st item.", NULL);
	add_item(root_list, " 7-st item.", NULL);
	add_item(root_list, " 8-st item.", NULL);
	add_item(root_list, " 9-st item.", NULL);
	add_item(root_list, "10-st item.", NULL);
	add_item(root_list, "11-st item.", NULL);
	add_item(root_list, "12-st item.", NULL);
	add_item(root_list, "13-st item.", NULL);

	add_list(root_list, root_list->edge);
	list = root_list->edge->child;

	add_item(list, "SUBMENU: fitst item.", NULL);
	add_item(list, "SUBMENU:  1-st item.", NULL);
	add_item(list, "SUBMENU:  2-st item.", NULL);
	add_item(list, "SUBMENU:  3-st item.", NULL);
	add_item(list, "SUBMENU:  4-st item.", NULL);
	add_item(list, "SUBMENU:  5-st item.", NULL);
	add_item(list, "SUBMENU:  6-st item.", NULL);
	add_item(list, "SUBMENU:  7-st item.", NULL);
	add_item(list, "SUBMENU:  8-st item.", NULL);
	add_item(list, "SUBMENU:  9-st item.", NULL);
	add_item(list, "SUBMENU: 10-st item.", NULL);
	add_item(list, "SUBMENU: 11-st item.", NULL);
	add_item(list, "SUBMENU: 12-st item.", NULL);
	add_item(list, "SUBMENU: 13-st item.", NULL);

	return root_list;
}
