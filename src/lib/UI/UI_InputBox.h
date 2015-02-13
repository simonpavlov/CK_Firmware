#ifndef UI_INPUTBOX
#define UI_INPUTBOX

#include <string>

#include "UI_Task.h"
#include "UI_Font.h"
#include "UI_Main.h"

// Realization in src/UI_InputBox.cpp


class InputBox: public Task{
	public:
		class Callback{
			public:
				virtual void exec(const std::string &str) = 0;
		};

		InputBox(UI &stk, const std::string &prompt, InputBox::Callback *init_cb);
		~InputBox();

		result 	up();
		result	down();
		result	select();
		result	back();
		Surface	& draw();

	private:
		static const std::string InputCharsRange;
		static const unsigned int InputLenght;

		int			cur_char;
		std::string	res_str;
		Callback	*m_callback;
		Surface		surf;
		Font		*m_font;
};

#endif //UI_INPUTBOX
