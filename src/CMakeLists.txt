set (APPNAME main)
set (${APPNAME}_SRCS
    ${APPNAME}.c)

add_executable (${APPNAME} ${${APPNAME}_SRCS})
target_link_libraries (${APPNAME} emul menu ${SDL_LIBRARY})
