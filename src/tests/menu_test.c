#include <emul/emulator.h>
#include <menu/menu.h>

int main(){
	emul_init(320, 240);
	atexit(emul_quit);

	menu_init(get_video_buffer(), 320, 240);

	if(font_init("Lat2-VGA32x16.psf") == NORMAL){
		//font_stdout();
		
		draw_char('S', 128, 0);
	}

	refresh_video_buffer();

	while(1){ //Зацикливание до тех пор пока не закроем эмулятор
		if(get_event() == EVT_EXIT){
			printf("Goodbye!\n");
			return 0;
		}

		SDL_Delay(100);
	}
	return 0;
}
