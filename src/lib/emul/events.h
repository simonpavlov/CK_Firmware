#ifndef EMUL_EVENTS
#define EMUL_EVENTS

#include <SDL/SDL.h>

enum Event {
	EVT_NOTHING = 0,	//Ничего не произошло
	EVT_EXIT,			//Событие выхода
	EVT_PRESS_DOWN,		//Нажата кнопка вниз
	EVT_PRESS_UP,		//Нажата кнопка вверх
	EVT_PRESS_ENTER		//Нажат enter
};

enum Event get_event(); //Функция возвращает событие.
						//В случае когда событий много,
						//новое затирает старое

#endif