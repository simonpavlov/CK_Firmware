#include "../video.h"

//#define DEBUG_VIDEO

SDL_Surface *Screen	= NULL;
ScreenInfo MainScreen;

unsigned int width_init;
unsigned int height_init;

void set_screen_res(unsigned int wth, unsigned int hht){
	width_init = wth;
	height_init = hht;
}

char video_init(){
	MainScreen.width = width_init;
	MainScreen.height = height_init;

	if(SDL_Init(SDL_INIT_VIDEO) != 0){
		return -1;
	}

	if((Screen = SDL_SetVideoMode(MainScreen.width, MainScreen.height, 32, SDL_SWSURFACE)) == NULL){
		return -1;
	}

	MainScreen.len_byte = (MainScreen.width * MainScreen.height + 7) / 8;
	if((MainScreen.buffer = (char *)malloc(MainScreen.len_byte)) == NULL){
		return -1;
	}
	memset(MainScreen.buffer, 0, MainScreen.len_byte);

	return 0;
}

ScreenInfo * get_screen_info(){
	return &MainScreen;
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

	for(y = 0; y < MainScreen.height; y++){

			#ifdef DEBUG
			printf("%3d: ", y);
			#endif

		for(x = 0; x < MainScreen.width; x++){
			pix_numb = y * MainScreen.width + x;
			color = ((*(MainScreen.buffer + pix_numb / 8) >> (7 - pix_numb % 8)) & 1)?
				brush: background;

			buf = (Uint32 *) Screen->pixels + y * Screen->pitch / 4 + x;

			*buf = color;

				#ifdef DEBUG
				printf("%c", ((*(MainScreen.buffer + pix_numb / 8) >> (7 - pix_numb % 8)) & 1)? '#': '_');
				#endif
		}

			#ifdef DEBUG
			printf("\n");
			#endif
	}

	SDL_Flip(Screen);
}

void video_quit(){
	SDL_FreeSurface(Screen);

	#ifdef DEBUG_VIDEO
	printf("Trying SDL_Quti()\n");
	#endif
	SDL_Quit();
	#ifdef DEBUG_VIDEO
	printf("SDL_Quti() OK\n");
	#endif


	#ifdef DEBUG_VIDEO
	printf("Trying free()\n");
	#endif
	free(MainScreen.buffer);
	#ifdef DEBUG_VIDEO
	printf("free OK\n");
	#endif
}
