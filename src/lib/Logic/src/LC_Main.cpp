#include "../LC_Main.h"

#include <IO/CK_Logger.h>
#include <emul/emulator.h>
#include <IO/CK_Logger.h>
#include <Uni3_Terminus20x10_psf.h>

#include <iostream>
#include <vector>
#include <string>

#define DEBUG_LOGIC 1
#define LDBG DEBUG_LOGIC && DBG

Logic::Logic():
	m_stor(),
	m_ui(Font(Uni3_Terminus20x10_psf))
{
	// Logger initialization
	Logger::set_output(&std::cout);
	LDBG << "IN Logic::Logic()" << std::endl;

	Box::init_Boxis(m_ui);
	Callback::init_Callbacks(this);

	callbacks.push(new main_list());
}

Logic::~Logic(){
	LDBG << "IN Logic::~Logic()" << std::endl;
}

void Logic::loop(){
	bool run_flag = true;
	while(run_flag){
		switch(char(get_event())){
			case EVT_EXIT:
				LDBG << "EVT_EXIT" << std::endl;
				run_flag = false;
			break;

			case EVT_PRESS_UP:
				LDBG << "EVT_PRESS_UP" << std::endl;
				m_ui.up();
			break;

			case EVT_PRESS_DOWN:
				LDBG << "EVT_PRESS_DOWN" << std::endl;
				m_ui.down();
			break;

			case EVT_PRESS_ENTER:
				LDBG << "EVT_PRESS_ENTER" << std::endl;
				m_ui.select();
			break;

			case EVT_PRESS_BACK:
				LDBG << "EVT_PRESS_BACK" << std::endl;
				m_ui.back();
			break;
		}

		m_ui.draw();
		callbacks.top()->run();
		if(!m_ui.get_box()) run_flag = false;
	}
}
