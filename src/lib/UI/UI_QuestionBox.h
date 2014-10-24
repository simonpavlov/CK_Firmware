#ifndef UI_QUESTIONBOX
#define UI_QUESTIONBOX

#include <string>
#include <algorithm>

#include "UI_Task.h"
#include "UI_Font.h"

/*
	Этот класс реализует окно - вопрос
*/

class QuestionBox: public Task{
	private:
		Surface *surf, *yes_surf, *no_surf, *quest_surf;

		int cur_item;

	public:
		// str - Вопрос, cb - обработчик
		QuestionBox(UI &stk, std::string str, Callback *cb);
		~QuestionBox();

		bool 	up();
		bool	down();
		bool	select();
		Surface	& draw();
};

#endif //UI_QUESTIONBOX
