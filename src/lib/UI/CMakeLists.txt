set (MENU_SRC
	src/UI.c
	src/UI_font.c
	src/UI_tree.c
	src/UI_menu.c
	)

add_definitions (-D DEBUG)

add_library (menu ${MENU_SRC})
