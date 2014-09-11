#include <emul/emulator.h>
#include <UI/UI.h>

#include <Uni3_Terminus20x10_psf.h>

int main(){
	emul_init(320, 240);
	atexit(emul_quit);

	CKF_Font *font, *test_font;

	//test_font = ffont_init("experiment/Pixel-UniCode.psf");

	font = bfont_init(Uni3_Terminus20x10_psf);
	if(!font){
		printf("Font 2 not load.\n");
		return 0xFFFFF;
	}

	UI_init(get_screen_info(), font);

	printf("\n");

	//draw_string(font, "draw_string(font, \"this_string\", 43, 200);",  0, 200);
	//draw_string(font, "draw_string(font, \"this_string\", 43, 200);", 50, 100);
	//draw_string(test_font, "Pixel-Unicode.psf", 10, 0);

	UI_draw();

	while(1){ //Зацикливание до тех пор пока не закроем эмулятор

		switch(get_event()){
			case EVT_EXIT:
				printf("Goodbye!\n");
				return 0;
				break;

			case EVT_PRESS_UP:
				UI_up();
				UI_clear_src();
				UI_draw();
				break;

			case EVT_PRESS_DOWN:
				UI_down();
				UI_clear_src();
				UI_draw();
				break;

			case EVT_PRESS_ENTER:
				UI_enter();
				UI_clear_src();
				UI_draw();
				break;
		}

		refresh_video_buffer();
		SDL_Delay(10);
	}
	return 0;
}
