#include "../UI_SelectBox.h"

#include <iostream>

SelectBox::SelectBox(UI &stk, std::vector<std::string> &str_mass, Callback *cb):
	Task(stk, cb),
	menu_items(str_mass),
	max_width(stk.get_width()),
	max_height(stk.get_height()),
	first_item(0),
	cur_item(0),
	interval(0),
	up_set(0),
	right_set(0)
{
	//TODO: переделать инициализацию
	Font font = my_UI.get_default_font();

	max_str = (max_height - up_set) / (font.get_height() + interval);

	last_item = max_str < menu_items.size()? max_str: menu_items.size();

	if(max_str > last_item) max_str = last_item;

	last_item--;

	int hht, desired_hht;
	desired_hht = max_str * (font.get_height() + interval) + right_set;
	if((signed int) max_height - desired_hht > 0) hht = desired_hht;
	else hht = max_height;

	#ifdef DEBUG_UI_SELECTBOX
	std::cout << "width: " << max_width << std::endl;
	std::cout << "height: " << hht << std::endl;
	#endif

	surf = new Surface(max_width, hht);
}

SelectBox::~SelectBox(){
	delete surf;
}

void SelectBox::up(){
	cur_item--;

	if(cur_item == first_item && first_item != 0){
		first_item--;
		last_item--;
	}

	if(cur_item < 0){
		cur_item = menu_items.size() - 1;
		first_item = menu_items.size() - max_str;
		last_item = first_item + max_str;
	}
}

void SelectBox::down(){
	cur_item++;
	if(cur_item == last_item && last_item != menu_items.size() - 1){
		first_item++;
		last_item++;
	}
	if(cur_item > menu_items.size() - 1){
		cur_item = 0;
		first_item = 0;
		last_item = first_item + max_str - 1;
	}
}

void SelectBox::select(){
	callback->exec(cur_item);
}

Surface & SelectBox::draw(){
	#ifdef DEBUG_UI_SELECTBOX
	std::cout << "first_item: " << first_item << std::endl;
	std::cout << "cur_item: " << cur_item << std::endl;
	std::cout << "last_item: " << last_item << std::endl;
	#endif

	Font font = my_UI.get_default_font();

	surf->clear();

	Surface *str_surf;

	int y = (cur_item - first_item) * (font.get_height() + interval) + up_set;

	// FIXME:
	Surface ch_surf = font.gen_surf('>');
	surf->draw(ch_surf, right_set, y);

	for(int i = 0; i < max_str; i++){
		str_surf = &font.gen_surf(	menu_items[i + first_item],
									max_width - right_set - font.get_width());
		surf->draw(	*str_surf,
					right_set + font.get_width(),
					i * (font.get_height() + interval) + up_set);

		delete str_surf;
	}

	surf->draw_border();

	return *surf;
}