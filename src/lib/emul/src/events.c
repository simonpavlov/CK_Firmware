#include "../events.h"

enum Event get_event(){
	SDL_Event evt;

	int i;
	for(i = 0; SDL_PollEvent(&evt); i++);

	if(i == 0) return EVT_NOTHING;

	switch(evt.type){
		case SDL_QUIT:
			#ifdef DEBUG
				printf("SDL_QUIT\n");
			#endif

			return EVT_EXIT;

			break;

		case SDL_KEYDOWN:
			if(evt.key.keysym.sym == SDLK_UP){
				#ifdef DEBUG
					printf("SDLK_UP\n");
				#endif

				return EVT_PRESS_UP;
			}
			else if(evt.key.keysym.sym == SDLK_DOWN){
				#ifdef DEBUG
					printf("SDLK_DOWN\n");
				#endif

				return EVT_PRESS_DOWN;
			}
			else if(evt.key.keysym.sym == SDLK_RETURN){
				#ifdef DEBUG
					printf("SDLK_RETURN\n");
				#endif

				return EVT_PRESS_ENTER;
			}

			break;

		default:
			return EVT_NOTHING;
	}
}

