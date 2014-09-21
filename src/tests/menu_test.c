#include <emul/emulator.h>
#include <UI/UI.h>

#include <Uni3_Terminus20x10_psf.h>

typedef struct {
	// Unical identifier
	uint64_t ident;
	// Battery state in percents
	uint8_t  batteryState;
	// Avaliable flash password space in bytes
	uint32_t freePasswordSpace;
	// Avaliable flash key space in bytes
	uint32_t freeKeySpace;
} DeviceInfo;

int main(){
	emul_init(320, 240);
	atexit(emul_quit);

	CKF_Font *font, *test_font;
	// UI_surface *surf = UI_surf_init(16, 10);

	// int i;
	// for(i = 0; i < 20; i++){
	// 	*(surf->buffer + i) = 255;
	// }

	//test_font = ffont_init("experiment/Pixel-UniCode.psf");

	font = bfont_init(Uni3_Terminus20x10_psf);
	if(!font){
		printf("Font 2 not load.\n");
		return 0xFFFFF;
	}

	UI_init(get_screen_info(), font);

	// for(i = 0; i < 5; i++){
	// 	UI_draw_surf(surf, 21 + 3 * i, 9 + i * surf->height);
	// }

	printf("\n");

	//draw_string(font, "draw_string(font, \"this_string\", 43, 200);",  0, 200);
	//draw_string(font, "draw_string(font, \"this_string\", 43, 200);", 50, 100);
	//draw_string(test_font, "Pixel-Unicode.psf", 10, 0);

	UI_draw();

	/*
	unsigned char comm_buf[5000];
	DeviceInfo info;
	info.ident = 123456;
	if (fork())
		while (1) {
			// Коммуникационная часть
			short readed = comm_recv(comm_buf, 1);
			if (readed) {
				fprintf(stderr, "Readed\n");
				if (*comm_buf == 0xF0) {
					fprintf(stderr,"Init command\n");
					comm_send(comm_buf, 1);
				}
				if (*comm_buf == 0xF1) {
					fprintf(stderr, "Device info command\n");
					comm_send(comm_buf, 1);
					comm_send((char *) &info, sizeof(DeviceInfo));
				}
			}
		}
	*/

	while(1){ //Зацикливание до тех пор пока не закроем эмулятор
		// Графическая часть
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
