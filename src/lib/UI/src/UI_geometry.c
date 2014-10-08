#include "../UI_geometry.h"

void UI_draw_pix(UI_surface *surf, int x, int y){
	char *ned_byte = (surf->buffer + y * surf->width / 8) + x / 8;
	*ned_byte |= 1 << (7 - x % 8);
}

void UI_draw_pargram(UI_surface *surf, int x, int y, int width, int height){
	int i;

	for(i = x; i <= x + width; i++){
		UI_draw_pix(surf, i, y);
		UI_draw_pix(surf, i, y + height);
	}

	for(i = y + 1; i < y + height; i++){
		UI_draw_pix(surf, x, i);
		UI_draw_pix(surf, x + width, i);
	}
}