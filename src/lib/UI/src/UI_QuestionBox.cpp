#include "../UI_QuestionBox.h"

QuestionBox::QuestionBox(UI &stk, std::string str, Callback *cb):
	Task(stk, cb),
	cur_item(0)
{
	Font font = my_UI.get_default_font();

	int wht, hht,
		max_width = my_UI.get_width(),
		max_height = my_UI.get_height();

	quest_surf	= &font.gen_surf(str, my_UI.get_width());
	yes_surf	= &font.gen_surf(std::string("Yes"));
	no_surf		= &font.gen_surf(std::string("No"));

	wht = std::max(std::min(my_UI.get_width(), quest_surf->get_width() + 16), no_surf->get_width() + yes_surf->get_width() + 24);
	hht = 2 * font.get_height() + 12;

	surf = new Surface(wht, hht);
}

QuestionBox::~QuestionBox(){
	delete quest_surf;
	delete yes_surf;
	delete no_surf;
	delete surf;
}

bool QuestionBox::up(){
	cur_item = (cur_item + 1) % 2;

	return true;
}

bool QuestionBox::down(){
	cur_item = (cur_item + 1) % 2;

	return true;
}

bool QuestionBox::select(){
	int res = cur_item;
	callback->exec(res);

	return false;
}

Surface	& QuestionBox::draw(){
	surf->clear();

	Font font = my_UI.get_default_font();

	int	surf_width	= surf->get_width(),
		no_width	= no_surf->get_width(),
		yes_width	= yes_surf->get_width(),
		interval	= 5;

	surf->draw_border();
	surf->draw(*quest_surf, (surf_width - quest_surf->get_width()) / 2, 3);

	int	x = (surf_width - no_width - yes_width - interval) / 2,
		y = 6 + 1 + font.get_height();

	surf->draw(*no_surf, x, y);
	surf->draw(*yes_surf, x + no_width + interval, y);

	surf->draw(x - 4 + cur_item * (no_width + interval)
		, y - 1,
		font.get_width() * (2 + cur_item) + 6,
		font.get_height());

	return *surf;
}