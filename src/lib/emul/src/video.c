#include "../video.h"

extern SDL_Surface *Screen;
extern char *Display;
extern int DispW, DispH;

char * get_video_buffer(){
	return Display;
}

void refresh_video_buffer(){
	Uint32 background;
	Uint32 brush;
	Uint32 color;

	brush		= SDL_MapRGB(Screen->format, 255, 255, 255);
	background	= SDL_MapRGB(Screen->format,   0,   0,   0);

	int x, y;
	Uint32 pix_numb;
	Uint32 *buf;

	for(y = 0; y < DispH; y++){

#ifdef DEBUG
			printf("%3d: ", y);
#endif

		for(x = 0; x < DispW; x++){
			pix_numb = y * DispW + x;
			color = ((*(Display + pix_numb / 8) >> (7 - pix_numb % 8)) & 1)?
				brush: background;

			buf = (Uint32 *) Screen->pixels + y * Screen->pitch / 4 + x;

			*buf = color;

#ifdef DEBUG
				printf("%c", ((*(Display + pix_numb / 8) >> (7 - pix_numb % 8)) & 1)? '#': '_');
#endif
		}

#ifdef DEBUG
			printf("\n");
#endif
	}

	SDL_Flip(Screen);
}
