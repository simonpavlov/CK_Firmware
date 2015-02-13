#include "../UI_SelectBox.h"

#include <iostream>

SelectBox::SelectBox(UI &init_ui, std::vector<std::string> &str_mass, Callback *cb):
	m_callback(cb),
	menu_items(str_mass),
	max_width(init_ui.get_width()),
	max_height(init_ui.get_height()),
	first_item(0),
	cur_item(0),
	interval(0),
	up_set(0),
	right_set(0)
{
	//TODO: переделать инициализацию
	m_font = &init_ui.get_default_font();

	max_str = (max_height - up_set) / (m_font->get_height() + interval);

	last_item = max_str < menu_items.size()? max_str: menu_items.size();

	if(max_str > last_item) max_str = last_item;

	last_item--;

	int hht, desired_hht;
	desired_hht = max_str * (m_font->get_height() + interval) + right_set;
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

Task::result SelectBox::up(){
	if(menu_items.size() <= 1) return none;

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

	return surf_changed;
}

Task::result SelectBox::down(){
	if(menu_items.size() <= 1) return none;

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

	return surf_changed;
}

Task::result SelectBox::select(){
	m_callback->exec(cur_item);

	return complite;
}

Surface & SelectBox::draw(){
	#ifdef DEBUG_UI_SELECTBOX
	std::cout << "first_item: " << first_item << std::endl;
	std::cout << "cur_item: " << cur_item << std::endl;
	std::cout << "last_item: " << last_item << std::endl;
	#endif

	surf->clear();

	Surface *str_surf;

	int y = (cur_item - first_item) * (m_font->get_height() + interval) + up_set;
	Surface *ch_surf = m_font->gen_surf('>');
	surf->draw(*ch_surf, right_set, y);
	delete ch_surf;

	for(unsigned int i = 0; i < max_str; i++){
		str_surf = m_font->gen_surf(menu_items[i + first_item],
									max_width - right_set - m_font->get_width());
		surf->draw(	*str_surf,
					right_set + m_font->get_width(),
					i * (m_font->get_height() + interval) + up_set);

		delete str_surf;
	}

	surf->draw_border();

	return *surf;
}
