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
	public:
		class Callback{
			public:
				virtual void exec(bool answer) = 0;
		};

		// str - Вопрос, cb - обработчик
		QuestionBox(UI &init_ui, std::string str, Callback *cb);
		~QuestionBox();

		bool 	up();
		bool	down();
		bool	select();
		bool	back(){return false;}
		Surface	& draw();

	private:
		Callback *m_callback;

		Surface *surf, *yes_surf, *no_surf, *quest_surf;

		int cur_item;
};

#endif //UI_QUESTIONBOX
