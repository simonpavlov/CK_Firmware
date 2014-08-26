#ifndef EMUL_VIDEO
#define EMUL_VIDEO

#include <SDL/SDL.h>
#include "manager.h"

/*
 * Возвращает указатель на буфер видеопамяти
 */
ScreenInfo * get_screen_info();

/*
 * Синхронизирует буфер и экран
 */
void refresh_video_buffer();

#endif
