#ifndef UI_SELECTBOX
#define UI_SELECTBOX

#include <string>
#include <vector>

#include "UI_Box.h"
#include "UI_Font.h"
#include "UI_Main.h"

// Realization in src/UI_SelectBox.cpp

/*
	Этот клас реализует ... select box
*/
class SelectBox: public Box{
	public:
		// str_mass - пункты меню, callback_f - обработчик
		SelectBox(std::vector<std::string> &str_mass);
		~SelectBox();

		size_t	get_res(){m_stat = none; return m_res;}

		Status 	up();
		Status	down();
		Status	select();
		Status	back(){return m_stat = none;}
		Surface	& draw();

	private:
		size_t		m_res;

		Surface		*surf;
		Font		*m_font;
		std::vector<std::string> menu_items;
		unsigned int max_str, last_item, max_width, max_height;
		int first_item, cur_item, interval, up_set, right_set;
};

#endif //UI_SELECTBOX
