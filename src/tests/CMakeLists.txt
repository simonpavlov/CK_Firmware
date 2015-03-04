add_executable (main_test main_test.cpp)
target_link_libraries (main_test UI IO emul ${SDL_LIBRARY})

add_executable (emul_test emul_test.c)
target_link_libraries (emul_test emul ${SDL_LIBRARY})

add_executable (IO_Serial_test IO_Serial_test.cpp)
target_link_libraries (IO_Serial_test emul IO ${SDL_LIBRARY})

add_executable (CK_string_test CK_string_test.cpp)
target_link_libraries (CK_string_test IO)

add_executable (IO_test IO_test.cpp)
target_link_libraries (IO_test IO emul ${SDL_LIBRARY})

add_executable (CK_Array_test CK_Array_test.cpp)
target_link_libraries (CK_Array_test IO emul ${SDL_LIBRARY})

add_executable (IO_ByteStream_test IO_ByteStream_test.cpp)
target_link_libraries (IO_ByteStream_test IO emul ${SDL_LIBRARY})

add_executable (CK_Logger_test CK_Logger_test.cpp)
target_link_libraries (CK_Logger_test IO emul ${SDL_LIBRARY})

add_executable (Storage_ff_test Storage_ff_test.cpp)
target_link_libraries (Storage_ff_test Storage emul ${SDL_LIBRARY})

add_executable (Storage_test Storage_test.cpp)
target_link_libraries (Storage_test IO Storage emul ${SDL_LIBRARY})

add_executable (LC_test LC_test.cpp)
target_link_libraries (LC_test Logic UI Storage IO emul ${SDL_LIBRARY})
