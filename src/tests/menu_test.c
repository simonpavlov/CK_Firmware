#include <emul/emulator.h>
#include <menu/menu.h>

#include <Uni2_VGA28x16_psf.h>

int main(){
	emul_init(320, 240);
	atexit(emul_quit);

	menu_init(get_video_buffer(), 320, 240);

	CKF_Font *font1, *font2;

	font1 = ffont_init("Lat2-VGA32x16.psf");
	if(!font1){
		printf("Font 1 not load.\n");
		return 0xFFFFF;
	}

	printf("\n");

	font2 = bfont_init(Uni2_VGA28x16_psf);
	if(!font2){
		printf("Font 2 not load.\n");
		return 0xFFFFF;
	}

	printf("\n");

	//font_stdout(font1);	
	//font_stdout(font2);

	int i;
	for(i = 0; i < 5; i++){
		draw_char(font1, 200, 80 + i, 10 + i * 32);
	}
	for(i = 0; i < 5; i++){
		draw_char(font2, 200, 100 + i, 10 + i * 32);
	}

	draw_string(font2, "draw_string(font2, \"this_string\", 43, 200);", 43, 200);

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
