#include "../UI_MessageBox.h"

#include <iostream>

MessageBox::MessageBox(UI &stk, std::string str, Callback *cb):
	Task(stk, cb),
	message(str)
{
	int	max_width = my_UI.get_width(),
		max_height = my_UI.get_height();

	Font font = my_UI.get_default_font();

	std::string ok = "OK";

	Surface &message_surf = font.gen_surf(str, max_width);
	Surface &OK_surf = font.gen_surf(ok, max_width);

	int wth, desired_wth;
	desired_wth = ((message_surf.get_width() + 7) / 8 + 2) * 8;
	if((signed int) max_width - desired_wth > 0) wth = desired_wth;
	else wth = max_width;

	#ifdef DEBUG_UI_MESSAGEBOX
	std::cout << "max_width: " << max_width << std::endl;
	std::cout << "wth: " << wth << std::endl;
	std::cout << "desired_wth: " << desired_wth << std::endl;
	std::cout << "max_width - desired_wth: " << (signed int) max_width - desired_wth << std::endl;
	#endif

	surf = new Surface(wth, 2 * font.get_height() + 12);

	surf->draw_border();
	surf->draw(message_surf, (surf->get_width() - message_surf.get_width()) / 2, 3);

	int	x = (surf->get_width() - OK_surf.get_width()) / 2,
		y = 6 + 1 + font.get_height();
	surf->draw(OK_surf, x, y);
	surf->draw(x - 4, y - 1, font.get_width() * 2 + 6, font.get_height());

	delete &OK_surf;
	delete &message_surf;
}

MessageBox::~MessageBox(){
	delete surf;
}

void MessageBox::select(){
	if(callback){
		callback->exec(0);
	}
	else{
		suicide();
	}
}

Surface & MessageBox::draw(){
	return *surf;
}