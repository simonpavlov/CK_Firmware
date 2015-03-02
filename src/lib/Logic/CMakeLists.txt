set (LOGIC_SRC
	src/LC_Callback.cpp
	src/Logic.cpp
	)

# add_definitions (-D DEBUG)

add_library (Logic ${LOGIC_SRC})
