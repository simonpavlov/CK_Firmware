#ifndef UI_SELECTBOX
#define UI_SELECTBOX

#include <string>
#include <vector>

#include "UI_Task.h"
#include "UI_Main.h"
#include "UI_Font.h"

/*
	Этот клас реализует ... select box
*/
class SelectBox: public Task{
	private:
		Surface *surf;
		Font &font;

		std::vector<std::string> &menu_items;
		void (*call_back)(std::string &str);
		unsigned int max_width, max_height;

		int first_item, cur_item, last_item, max_str, interval, up_set, right_set;

	public:
		// str_mass - пункты меню, call_back_f - обработчик
		SelectBox(UI &stk, std::vector<std::string> &str_mass, void (*call_back_f)(std::string &str));
		~SelectBox();

		void 	up();
		void	down();
		void	select();
		Surface	& draw();
};

#endif //UI_SELECTBOX
