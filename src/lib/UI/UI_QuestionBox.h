#ifndef UI_QUESTIONBOX
#define UI_QUESTIONBOX

#include <string>
#include <algorithm>

#include "UI_Box.h"
#include "UI_Font.h"
#include "UI_Main.h"

// Realization in src/UI_QuestionBox.cpp

/*
	Этот класс реализует окно - вопрос
*/

class QuestionBox: public Box{
	public:
		class Callback{
			public:
				virtual void exec(bool answer) = 0;
		};

		// str - Вопрос, cb - обработчик
		QuestionBox(std::string str, Callback *cb);
		~QuestionBox();

		Status 	up();
		Status	down();
		Status	select();
		Status	back(){return none;}
		Surface	& draw();

	private:
		Callback	*m_callback;
		Font		*m_font;	
		Surface		*surf, *yes_surf, *no_surf, *quest_surf;
		int			cur_item;
};

#endif //UI_QUESTIONBOX
