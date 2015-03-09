#include "../UI_Main.h"

#include <iostream>
#include <cassert>
#include <IO/CK_Logger.h>

#define DEBUG_UI_MAIN 1
#define LDBG DEBUG_UI_MAIN && DBG

UI::UI(Font font):
	m_box(NULL),
	default_font(font)
{
	LDBG << "IN UI::UI()" << std::endl;

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
	LDBG << "IN UI::~UI()" << std::endl;

	emul_quit(VIDEO_SYS);
}

Box * UI::push(Box *box){
	Box *last_box;

	last_box	= m_box;
	m_box		= box;

	LDBG << "NEED REFRESH" << std::endl;

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
			LDBG << "EVT_PRESS_UP" << std::endl;
			up();
			return true;

		case EVT_PRESS_DOWN:
			LDBG << "EVT_PRESS_DOWN" << std::endl;
			down();
			return true;

		case EVT_PRESS_ENTER:
			LDBG << "EVT_PRESS_ENTER" << std::endl;
			select();
			return true;

		case EVT_PRESS_BACK:
			LDBG << "EVT_PRESS_BACK" << std::endl;
			back();
			return true;
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
	bool res;

	res = m_box->select();

	need_refresh |= res;
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
	LDBG << "IN UI::clear_scr()" << std::endl;

	clear();
}
*/
