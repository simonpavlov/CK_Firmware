set (IO_SRC
	src/IO_Serial.cpp
	src/IO_Message.cpp
	)

# add_definitions (-D DEBUG)

add_library (IO ${IO_SRC})
