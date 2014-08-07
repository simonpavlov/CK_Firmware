#include "../manager.h"
#include <string.h>

SDL_Surface *Screen = NULL;
char *Display = NULL;
int DispW, DispH;

InitStatus emul_init(int width, int height){
	DispW = width;
	DispH = height;

	if(SDL_Init(SDL_INIT_VIDEO) != 0){
		return SDL_ERROR;
	}

	if((Screen = SDL_SetVideoMode(DispW, DispH, 32, SDL_SWSURFACE)) == NULL){
		return SDL_ERROR;
	}

    const int DispSize = (DispW * DispH + 7) / 8;
	if((Display = malloc(DispSize)) == NULL){
		return NO_MEMORY_ERROR;
	}
    memset(Display, 0, DispSize);

	return ALL_RIGHT;
}

void emul_quit(){
	SDL_FreeSurface(Screen);
	SDL_Quit();
	free(Display);
}
