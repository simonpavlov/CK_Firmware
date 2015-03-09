#ifndef UI_INPUTBOX
#define UI_INPUTBOX

#include <string>

#include "UI_Box.h"
#include "UI_Font.h"
#include "UI_Main.h"

// Realization in src/UI_InputBox.cpp


class InputBox: public Box{
	public:
		class Callback{
			public:
				virtual void exec(const std::string &str) = 0;
		};

		InputBox(const std::string &prompt, InputBox::Callback *init_cb);
		~InputBox();

		bool 	up();
		bool	down();
		bool	select();
		bool	back();
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
