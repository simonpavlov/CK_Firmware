#ifndef UI_INPUTBOX
#define UI_INPUTBOX

#include "UI_Task.h"
#include "UI_Font.h"

const char InputCharsRange[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};

class InputBox: public Task{
	public:
		class CallBack{
			public:
				virtual void exec(const char *str) = 0;
		};

	InputBox(const char *prompt, InputBox::CallBack *init_cb);
	~InputBox();

	bool 	up();
	bool	down();
	bool	select();
	Surface	& draw();

	private:
		InputBox::CallBack *m_cb;
		Surface *surf, *prompt_surf;
};

#endif //UI_INPUTBOX
