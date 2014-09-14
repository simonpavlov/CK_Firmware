#include "../UI_surface.h"
#include <stdlib.h>
#include <emul/emulator.h>

extern ScreenInfo *MenuScreen;

UI_surface * UI_surf_init(int w, int h){
	UI_surface *res_surf = malloc(sizeof(UI_surface));

	res_surf->len_byte	= (w * h + 7) / 8;
	res_surf->width		= w;
	res_surf->height	= h;

	res_surf->buffer	= malloc(res_surf->len_byte);

	memset(res_surf->buffer, 0, res_surf->len_byte);

	return res_surf;
}

void UI_surf_free(UI_surface *surf){
	free(surf->buffer);
	free(surf);
}

void UI_draw_surf(UI_surface * surf, int x, int y){
	int screen_width_byte, offset_byte;
	unsigned char *cur_byte_screen, *cur_byte_surf;

	screen_width_byte = MenuScreen->width / 8;
	offset_byte = x % 8;

	cur_byte_screen		= MenuScreen->buffer + y * screen_width_byte + x / 8;
	cur_byte_surf		= surf->buffer;

	int i_line;
	for(i_line = 0; i_line < surf->height; i_line++){
		int i_byte;

		for(i_byte = 0; i_byte < surf->width / 8; i_byte++){
			unsigned char output_byte = *(cur_byte_surf + i_byte);

			*(cur_byte_screen + i_byte)		|= output_byte >> offset_byte;
			*(cur_byte_screen + i_byte + 1)	|= output_byte << (8 - offset_byte);
		}

		cur_byte_screen	+= screen_width_byte;
		cur_byte_surf	+= surf->width / 8;
	}
}

void UI_clear_surf(UI_surface * surf){
	memset(surf->buffer, 0, surf->len_byte);
}

void UI_border(UI_surface *surf){
	unsigned char * cur_byte_surf;
	int i;

	cur_byte_surf = surf->buffer + surf->width / 8;
	for(i = 1; i < surf->height - 1; i++){
		*cur_byte_surf							|= 128;
		*(cur_byte_surf + surf->width / 8 - 1)	|= 1;

		cur_byte_surf += surf->width / 8;
	}

	for (i = 0; i < surf->width / 8; i++){
		*(surf->buffer + i) = 255;
		*(cur_byte_surf + i) = 255;
	}
}