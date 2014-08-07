#include "../menu.h"
#include <string.h>

int	FW_ScreenWidth;		//Ширина дисплея
int	FW_ScreenHeight;	//Высота дисплея
char	*FW_VideoBuffer;	//Ссылка на видео буфер

void menu_init(char *video_buffer, int width, int height){
	FW_VideoBuffer =	video_buffer;
	FW_ScreenWidth =	width;
	FW_ScreenHeight =	height;
}
