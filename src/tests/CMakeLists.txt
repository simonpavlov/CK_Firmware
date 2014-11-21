add_executable (main_test main_test.cpp)
target_link_libraries (main_test emul UI ${SDL_LIBRARY})

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

add_executable (CK_Loger_test CK_Loger_test.cpp)
target_link_libraries (CK_Loger_test IO emul ${SDL_LIBRARY})
