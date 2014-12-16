set (STORAGE_SRC
	src/Storage.cpp
	src/diskio.c
	src/ff.c
	src/option/unicode.c
	src/option/syscall.c
	)

# add_definitions (-D DEBUG)

add_library (Storage ${STORAGE_SRC})
