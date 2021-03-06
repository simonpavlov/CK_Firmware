//Программа для тестирования библиотеки emulator.h

#include <stdio.h>
#include <emul/emulator.h>

#define DISPW 32
#define DISPH 24

int main(){
	set_screen_res(DISPW, DISPH);

	if(emul_init(VIDEO_SYS) != ALL_RIGHT){ //Инициализация эмулятора
		return 1;
	}
	printf("***\n");

	char *buf = get_screen_info()->buffer;

	int i, j;
	for(i = 0; i < DISPW * DISPH / 8; i++){
		*(buf + i) = 0x2A; //Заполнение всех байтов буфера заначением 00101010
	}

	*buf = 1; //В первый байт 00000001

	for(i = 0; i < DISPH; i++){ //Дебаг буфера
		printf("%3d: ", i);
		for(j = 0; j < DISPW / 8; j++){
			printf("%X ", *(buf + i * DISPH / 8 + j));
		}
		printf("\n");
	}

	refresh_video_buffer();

	while(1){ //Зацикливание до тех пор пока не закроем эмулятор
		if(get_event() == EVT_EXIT){
			printf("Goodbye!\n");
			emul_quit(VIDEO_SYS);
			return 0;
		}

		SDL_Delay(100);
	}
}
