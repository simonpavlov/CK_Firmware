#include "../UI_InputBox.h"
#include <iostream>

#define DEBUG_UI_INPUT_BOX

const std::string InputBox::InputCharsRange = "0123456789";
const unsigned int InputBox::InputLenght = 6;

InputBox::InputBox(UI &stk, const std::string &prompt, InputBox::Callback *init_cb):
	cur_char(0),
	m_callback(init_cb),
	surf(240, stk.get_default_font().get_height() * 2 + 10)
{
	m_font = &stk.get_default_font();
	Surface *prompt_surf = m_font->gen_surf(prompt);

	surf.draw(*prompt_surf, 3, 0);
	surf.draw_border();

	delete prompt_surf;
}

InputBox::~InputBox(){}

Task::result InputBox::up(){
	#ifdef DEBUG_UI_INPUT_BOX
	std::cout << "IN InputBox::up()" << std::endl;
	#endif // DEBUG_UI_INPUT_BOX

	cur_char = (cur_char + 1) % InputCharsRange.size();

	#ifdef DEBUG_UI_INPUT_BOX
	std::cout << "cur_char: " << cur_char << std::endl;
	#endif // DEBUG_UI_INPUT_BOX	

	if(res_str.size() != InputLenght) return surf_changed;
	else return none;
}

Task::result InputBox::down(){
	#ifdef DEBUG_UI_INPUT_BOX
	std::cout << "IN InputBox::down()" << std::endl;
	#endif // DEBUG_UI_INPUT_BOX

	cur_char = (cur_char + InputCharsRange.size() - 1) % InputCharsRange.size();

	#ifdef DEBUG_UI_INPUT_BOX
	std::cout << "cur_char: " << cur_char << std::endl;
	#endif // DEBUG_UI_INPUT_BOX		

	if(res_str.size() != InputLenght) return surf_changed;
	else return none;
}

Task::result InputBox::select(){
	#ifdef DEBUG_UI_INPUT_BOX
	std::cout << "IN InputBox::select()" << std::endl;
	#endif // DEBUG_UI_INPUT_BOX

	if(res_str.size() < InputLenght)
		res_str.push_back(InputCharsRange[cur_char]);
	else{
		#ifdef DEBUG_UI_INPUT_BOX
		std::cout << "m_callback->exec(res_str)" << std::endl;
		#endif // DEBUG_UI_INPUT_BOX		
		m_callback->exec(res_str);
		return complite;
	}

	return surf_changed;
}

Task::result InputBox::back(){
	#ifdef DEBUG_UI_INPUT_BOX
	std::cout << "IN InputBox::back()" << std::endl;
	#endif // DEBUG_UI_INPUT_BOX

	if(res_str.size() > 0){
		res_str.erase(res_str.size() - 1);
	}

	return surf_changed;
}

Surface & InputBox::draw(){
	#ifdef DEBUG_UI_INPUT_BOX
	std::cout << "IN InputBox::draw()" << std::endl;
	std::cout << "res_str: " << res_str << std::endl;
	#endif // DEBUG_UI_INPUT_BOX

	std::string show_str = res_str;
	if(res_str.size() < InputLenght){
		show_str.push_back(InputCharsRange[cur_char]);
		show_str.push_back('<');
		for(unsigned int i = res_str.size(); i < InputLenght - 2; i++) show_str.push_back('.');
	}

	Surface *surf_show_str	= m_font->gen_surf(show_str);

	surf.draw(*surf_show_str, 3, m_font->get_height());
	surf.draw_border();

	delete surf_show_str;

	return surf;
}
