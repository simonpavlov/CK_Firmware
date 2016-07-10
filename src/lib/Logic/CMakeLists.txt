set (LOGIC_SRC
	src/LC_PasswordsTask.cpp
	src/LC_MessageTask.cpp
	src/LC_MainTask.cpp
	src/LC_TaskManager.cpp
	src/LC_Task.cpp
	src/LC_App.cpp
	)

# add_definitions (-D DEBUG)

add_library (Logic ${LOGIC_SRC})
