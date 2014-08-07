add_executable (menu_test menu_test.c)
target_link_libraries (menu_test emul menu ${SDL_LIBRARY})
add_executable (emul_test emul_test.c)
target_link_libraries (emul_test emul ${SDL_LIBRARY})
