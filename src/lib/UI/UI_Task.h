#ifndef UI_TASK
#define UI_TASK

#include "UI_Main.h"
#include "UI_Surface.h"

class UI;

/*
	Базовая задача
*/
class Task {
	protected:
		UI &my_UI;

	public:
		Task(UI &ui);
		~Task() {};

		virtual bool	up() = 0;
		virtual bool	down() = 0;
		virtual bool 	select() = 0;
		virtual bool	back() = 0;
		virtual Surface	& draw() = 0;

		void suicide();
};

#endif //UI_TASK
