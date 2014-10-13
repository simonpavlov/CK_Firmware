#include <emul/emulator.h>
#include <UI/UI.h>

#include <Uni3_Terminus20x10_psf.h>

int main(){
	emul_init(320, 240);
	atexit(emul_quit);

	// Surface surf(80, 20);

	while(1){ //Зацикливание до тех пор пока не закроем эмулятор
		// Графическая часть
		switch(get_event()){
			case EVT_EXIT:
				printf("Goodbye!\n");
				return 0;
				break;

			case EVT_PRESS_UP:
				break;

			case EVT_PRESS_DOWN:
				break;

			case EVT_PRESS_ENTER:
				break;
		}

		refresh_video_buffer();
		SDL_Delay(10);
	}
	return 0;
}
