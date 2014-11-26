#include "../UI_InputBox.h"
#include <iostream>

#define DEBUG_UI_INPUT_BOX

const std::string InputBox::InputCharsRange = "0123456789";
const unsigned int InputBox::InputLenght = 6;

InputBox::InputBox(UI &stk, const std::string &prompt, InputBox::Callback *init_cb):
	Task(stk),
	m_callback(init_cb),
	surf(240, stk.get_default_font().get_height() * 2 + 10),
	cur_char(0)
{
	Font font = my_UI.get_default_font();
	Surface &prompt_surf = font.gen_surf(prompt);

	surf.draw(prompt_surf, 3, 0);
	surf.draw_border();

	delete &prompt_surf;
}

InputBox::~InputBox(){}

bool InputBox::up(){
	#ifdef DEBUG_UI_INPUT_BOX
	std::cout << "IN InputBox::up()" << std::endl;
	#endif // DEBUG_UI_INPUT_BOX

	cur_char = (cur_char + 1) % InputCharsRange.size();

	#ifdef DEBUG_UI_INPUT_BOX
	std::cout << "cur_char: " << cur_char << std::endl;
	#endif // DEBUG_UI_INPUT_BOX	

	return true;
}

bool InputBox::down(){
	#ifdef DEBUG_UI_INPUT_BOX
	std::cout << "IN InputBox::down()" << std::endl;
	#endif // DEBUG_UI_INPUT_BOX

	cur_char = (cur_char + InputCharsRange.size() - 1) % InputCharsRange.size();

	#ifdef DEBUG_UI_INPUT_BOX
	std::cout << "cur_char: " << cur_char << std::endl;
	#endif // DEBUG_UI_INPUT_BOX		

	return true;
}

bool InputBox::select(){
	#ifdef DEBUG_UI_INPUT_BOX
	std::cout << "IN InputBox::select()" << std::endl;
	#endif // DEBUG_UI_INPUT_BOX

	if(res_str.size() < InputLenght)
		res_str.push_back(InputCharsRange[cur_char]);
	else
		m_callback->exec(res_str);


	return true;
}

bool InputBox::back(){
	#ifdef DEBUG_UI_INPUT_BOX
	std::cout << "IN InputBox::back()" << std::endl;
	#endif // DEBUG_UI_INPUT_BOX

	return true;
}

Surface & InputBox::draw(){
	#ifdef DEBUG_UI_INPUT_BOX
	std::cout << "IN InputBox::draw()" << std::endl;
	std::cout << "res_str: " << res_str << std::endl;
	#endif // DEBUG_UI_INPUT_BOX

	Font font = my_UI.get_default_font();

	Surface &surf_res_str = font.gen_surf(res_str);
	surf.draw(surf_res_str, 3, font.get_height());

	surf.draw_border();

	return surf;
}
