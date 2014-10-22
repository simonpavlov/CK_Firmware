set (MENU_SRC
	src/UI_QuestionBox.cpp
	src/UI_SelectBox.cpp
	src/UI_MessageBox.cpp
	src/UI_Task.cpp
	src/UI_Main.cpp
	src/UI_Font.cpp
	src/UI_Surface.cpp
	src/test_task.cpp
	)

# add_definitions (-D DEBUG)

add_library (UI ${MENU_SRC})
