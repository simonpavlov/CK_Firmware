#include "../UI_QuestionBox.h"

QuestionBox::QuestionBox(UI &init_ui, std::string str, Callback *cb):
	m_callback(cb),
	cur_item(0)
{
	m_font = &init_ui.get_default_font();

	int wht, hht,
		max_width = init_ui.get_width(),
		max_height = init_ui.get_height();

	quest_surf	= m_font->gen_surf(str, init_ui.get_width());
	yes_surf	= m_font->gen_surf(std::string("Yes"));
	no_surf		= m_font->gen_surf(std::string("No"));

	wht = std::max(std::min(init_ui.get_width(), quest_surf->get_width() + 16), no_surf->get_width() + yes_surf->get_width() + 24);
	hht = 2 * m_font->get_height() + 12;

	surf = new Surface(wht, hht);
}

QuestionBox::~QuestionBox(){
	delete quest_surf;
	delete yes_surf;
	delete no_surf;
	delete surf;
}

Task::result QuestionBox::up(){
	cur_item = (cur_item + 1) % 2;

	return surf_changed;
}

Task::result QuestionBox::down(){
	cur_item = (cur_item + 1) % 2;

	return surf_changed;
}

Task::result QuestionBox::select(){
	bool res = cur_item;
	m_callback->exec(res);

	return complite;
}

Surface	& QuestionBox::draw(){
	surf->clear();

	int	surf_width	= surf->get_width(),
		no_width	= no_surf->get_width(),
		yes_width	= yes_surf->get_width(),
		interval	= 5;

	surf->draw_border();
	surf->draw(*quest_surf, (surf_width - quest_surf->get_width()) / 2, 3);

	int	x = (surf_width - no_width - yes_width - interval) / 2,
		y = 6 + 1 + m_font->get_height();

	surf->draw(*no_surf, x, y);
	surf->draw(*yes_surf, x + no_width + interval, y);

	surf->draw(x - 4 + cur_item * (no_width + interval)
		, y - 1,
		m_font->get_width() * (2 + cur_item) + 6,
		m_font->get_height());

	return *surf;
}
