set (MENU_SRC
	src/UI.cpp
	)

add_definitions (-D DEBUG)

add_library (UI ${MENU_SRC})
