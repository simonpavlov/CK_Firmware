cmake_minimum_required (VERSION 2.6)
project (Firmware)

set (CMAKE_C_FLAGS_DEBUG "-D DEBUG")

link_directories (${CMAKE_BINARY_DIR}/../ext_lib)
include_directories (${CMAKE_BINARY_DIR}/../ext_lib)

find_package (SDL REQUIRED)
if (NOT SDL_FOUND)
 message (FATAL_ERROR "SDL not found!")
 return ()
endif (NOT SDL_FOUND)

add_subdirectory (src)
add_subdirectory (src/lib/menu)
