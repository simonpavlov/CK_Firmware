cmake_minimum_required (VERSION 2.6)
project (CKFirmware)

# set (CMAKE_C_FLAGS_DEBUG "-D DEBUG" -g)

include_directories (${CMAKE_SOURCE_DIR}/src/lib)
include_directories (${CMAKE_SOURCE_DIR}/data/fonts_in_headers)
include_directories (${CMAKE_SOURCE_DIR}/data/the_menu_structure)

find_package (SDL REQUIRED)
if (NOT SDL_FOUND)
 message (FATAL_ERROR "SDL not found!")
 return ()
endif (NOT SDL_FOUND)


add_subdirectory (src/tests)
add_subdirectory (src/lib/emul)
add_subdirectory (src/lib/UI)
add_subdirectory (src/lib/IO)
add_subdirectory (src/lib/Storage)
add_subdirectory (src/lib/Logic)
