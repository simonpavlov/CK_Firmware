#ifndef EMUL_VIDEO
#define EMUL_VIDEO

#include <SDL/SDL.h>

/*
 * Возвращает указатель на буфер видеопамяти
 */
char * get_video_buffer();

/*
 * Синхронизирует буфер и экран
 */
void refresh_video_buffer();

#endif
