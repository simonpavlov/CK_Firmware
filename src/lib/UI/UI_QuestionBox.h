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
		void (*callback)(bool res);
		Surface *surf, *yes_surf, *no_surf, *quest_surf;

		int cur_item;

	public:
		// str - Вопрос, call_back_f - callback функция
		QuestionBox(UI &stk, std::string str, void (*callback_f)(bool res));
		~QuestionBox();

		void 	up();
		void	down();
		void	select();
		Surface	& draw();
};

#endif //UI_QUESTIONBOX
