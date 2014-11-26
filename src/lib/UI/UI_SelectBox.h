#ifndef UI_SELECTBOX
#define UI_SELECTBOX

#include <string>
#include <vector>

#include "UI_Task.h"
#include "UI_Font.h"

/*
	Этот клас реализует ... select box
*/
class SelectBox: public Task{
	public:
		class Callback{
			public:
				virtual void exec(int number) = 0;
		};

		// str_mass - пункты меню, callback_f - обработчик
		SelectBox(UI &init_ui, std::vector<std::string> &str_mass, Callback *cb);
		~SelectBox();

		bool 	up();
		bool	down();
		bool	select();
		bool	back(){return false;}
		Surface	& draw();

	private:
		Callback *m_callback;
		Surface *surf;
		std::vector<std::string> menu_items;
		unsigned int max_width, max_height;
		int first_item, cur_item, last_item, max_str, interval, up_set, right_set;
};

#endif //UI_SELECTBOX
