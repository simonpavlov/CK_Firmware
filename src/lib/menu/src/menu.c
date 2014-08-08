#include "../menu.h"
#include <string.h>

int	CKF_ScreenWidth;		//Ширина дисплея
int	CKF_ScreenHeight;	//Высота дисплея
char	*CKF_VideoBuffer;	//Ссылка на видео буфер

void menu_init(char *video_buffer, int width, int height){
	CKF_VideoBuffer =	video_buffer;
	CKF_ScreenWidth =	width;
	CKF_ScreenHeight =	height;
}
