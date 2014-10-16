set (MENU_SRC
	src/Font.cpp
	src/test_task.cpp
	src/UI_Task.cpp
	src/UI_Main.cpp
	src/UI_Font.cpp
	src/UI_Surface.cpp
	)

# add_definitions (-D DEBUG)

add_library (UI ${MENU_SRC})
