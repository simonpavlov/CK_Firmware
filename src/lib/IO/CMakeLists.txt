set (IO_SRC
    src/IO.c
	src/serial.c
    src/message.c)

add_library (IO ${IO_SRC})
