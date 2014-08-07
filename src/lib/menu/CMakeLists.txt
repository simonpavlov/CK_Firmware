set (MENU_SRC
	src/font.c
	src/menu.c
	)

add_definitions (-D DEBUG)

add_library (menu ${MENU_SRC})
