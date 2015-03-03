#include "../UI_Main.h"

#include <iostream>
#include <cassert>

#define DEBUG_UI_MAIN

UI::UI(Font font):
	m_box(NULL),
	default_font(font)
{
	#ifdef DEBUG_UI_MAIN
	std::cout << "IN UI::UI()" << std::endl;
	#endif

	set_screen_res(320, 240);
	emul_init(VIDEO_SYS);

	ScreenInfo scr = *get_screen_info();
	assert(scr.width % 8 == 0);

	width			= scr.width;
	height			= scr.height;
	buf_size		= scr.len_byte;
	buffer			= (unsigned char *) scr.buffer;

	surf_is_my		= false;

	need_refresh	= false;
}

UI::~UI(){
	#ifdef DEBUG_UI_MAIN
	std::cout << "IN UI::~UI()" << std::endl;
	#endif

	emul_quit(VIDEO_SYS);
}

Box * UI::push(Box *box){
	Box *last_box;

	last_box	= m_box;
	m_box		= box;

	#ifdef DEBUG_UI_MAIN
	std::cout << "NEED REFRESH" << std::endl;
	#endif

	need_refresh = true;

	return last_box;
}

Box * UI::pop(){
	Box *last_box;

	last_box	= m_box;
	m_box		= NULL;

	//need_refresh = false;

	return last_box;
}

bool UI::process(Event evt){
	switch(char(evt)){
		case EVT_PRESS_UP:
			up();
			break;

		case EVT_PRESS_DOWN:
			down();
			break;

		case EVT_PRESS_ENTER:
			select();
			break;

		case EVT_PRESS_BACK:
			back();
			break;
	}

	return false;
}

void UI::up(){
	if(m_box->up()) need_refresh = true;
}

void UI::down(){
	if(m_box->down()) need_refresh = true;
}

void UI::select(){
	Box::Status res;

	res = m_box->select();

	if(res == Box::surf_changed) need_refresh = true;
}

void UI::back(){
	if(m_box->back()) need_refresh = true;
}

void UI::draw(){
	if(!m_box) return;

	if(need_refresh){
		clear();

		Surface &surf = m_box->draw();
		Surface::draw(surf);

		refresh_video_buffer();

		need_refresh = false;
	}
}

/*
void UI::clear_scr(){
	#ifdef DEBUG_UI_MAIN
	std::cout << "IN UI::clear_scr()" << std::endl;
	#endif

	clear();
}
*/
