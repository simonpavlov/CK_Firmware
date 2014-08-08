#include <emul/emulator.h>
#include <menu/menu.h>

int main(){
	emul_init(320, 240);
	atexit(emul_quit);

	menu_init(get_video_buffer(), 320, 240);

	CKF_Font * font;

	font = font_init("Lat2-VGA32x16.psf");
	if(!font){
		printf("Font not load.\n");
		return 0xFFFFF;
	}

	font_stdout(font);

	int i;
	for(i = 0; i < 5; i++){
		draw_char(font, 'D', 80 + i, 10 + i * 32);
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
