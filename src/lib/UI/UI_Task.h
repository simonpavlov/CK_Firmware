#ifndef UI_TASK
#define UI_TASK

#include "UI_Main.h"
#include "UI_Surface.h"
#include "UI_Callback.h"

class UI;

/*
	Базовая задача
*/
class Task {
	protected:
		UI &my_UI;
		Callback *callback;

	public:
		Task(UI &ui, Callback *cb);
		virtual ~Task() {};

		virtual void	up() = 0;
		virtual void	down() = 0;
		virtual void 	select() = 0;
		virtual Surface	& draw() = 0;

		void suicide();
};

#endif //UI_TASK
