#ifndef UI_GEOMETRY
#define UI_GEOMETRY

#include "UI_surface.h"

/*
	Нарисовать точку
*/
void UI_draw_pix(UI_surface *surf, int x, int y);

/*
	Нарисовать паралелограм
*/
void UI_draw_pargram(UI_surface *surf, int x, int y, int width, int height);

#endif