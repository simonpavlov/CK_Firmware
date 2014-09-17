#include "../manager.h"
#include <string.h>

SDL_Surface *Screen	= NULL;
ScreenInfo MainScreen;

InitStatus emul_init(int width, int height){
	MainScreen.width = width;
	MainScreen.height = height;

	if(SDL_Init(SDL_INIT_VIDEO) != 0){
		return SDL_ERROR;
	}

	if((Screen = SDL_SetVideoMode(MainScreen.width, MainScreen.height, 32, SDL_SWSURFACE)) == NULL){
		return SDL_ERROR;
	}

	MainScreen.len_byte = (MainScreen.width * MainScreen.height + 7) / 8;
	if((MainScreen.buffer = malloc(MainScreen.len_byte)) == NULL){
		return NO_MEMORY_ERROR;
	}
    memset(MainScreen.buffer, 0, MainScreen.len_byte);

#ifdef NETWORK_INIT
    network_init();
#endif

	return ALL_RIGHT;
}

void emul_quit(){
	SDL_FreeSurface(Screen);
	SDL_Quit();
	free(MainScreen.buffer);
}
