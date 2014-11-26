#ifndef UI_INPUTBOX
#define UI_INPUTBOX

#include <string>

#include "UI_Task.h"
#include "UI_Font.h"


class InputBox: public Task{
	public:
		class Callback{
			public:
				virtual void exec(const std::string &str) = 0;
		};

		InputBox(UI &stk, const std::string &prompt, InputBox::Callback *init_cb);
		~InputBox();

		bool 	up();
		bool	down();
		bool	select();
		bool	back();
		Surface	& draw();

	private:
		static const std::string InputCharsRange;
		static const unsigned int InputLenght;

		int cur_char;
		std::string res_str;
		Callback *m_callback;
		Surface surf;
};

#endif //UI_INPUTBOX
