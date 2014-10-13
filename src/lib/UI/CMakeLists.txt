set (MENU_SRC
	src/UI_Main.cpp
	src/UI_Font.cpp
	src/UI_Surface.cpp
	src/UI_Task.cpp
	)

# add_definitions (-D DEBUG)

add_library (UI ${MENU_SRC})
