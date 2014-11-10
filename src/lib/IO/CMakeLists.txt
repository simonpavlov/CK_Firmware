set (IO_SRC
	src/CK_string.cpp
	src/IO_Serial.cpp
	src/IO_Message.cpp
	)

# add_definitions (-D DEBUG)

add_library (IO ${IO_SRC})
