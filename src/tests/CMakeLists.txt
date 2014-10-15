add_executable (main_test main_test.cpp)
target_link_libraries (main_test emul UI ${SDL_LIBRARY})

add_executable (emul_test emul_test.c)
target_link_libraries (emul_test emul ${SDL_LIBRARY})
