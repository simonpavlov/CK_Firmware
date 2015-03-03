set (LOGIC_SRC
	src/LC_Callback.cpp
	src/LC_Main.cpp
	)

# add_definitions (-D DEBUG)

add_library (Logic ${LOGIC_SRC})
