set (emul_SRCS
	 src/events.c
	 src/video.c
	 src/manager.c)

add_library (emul ${emul_SRCS})
