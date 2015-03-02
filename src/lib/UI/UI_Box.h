#ifndef UI_TASK
#define UI_TASK

#include "UI_Surface.h"
#include <UI/UI_Main.h>

// Realization in src/UI_Box.cpp

class UI;

/*
	Базовая задача
*/
class Box {
	protected:
		static UI *o_ui;

	public:
		enum result {none, surf_changed, complite};

		static void init_Boxis(UI &ui){
			o_ui = &ui;
		}

		virtual ~Box() {};

		virtual result	up() = 0;
		virtual result	down() = 0;
		virtual result 	select() = 0;
		virtual result	back() = 0;
		virtual Surface	& draw() = 0;
};

#endif //UI_TASK
