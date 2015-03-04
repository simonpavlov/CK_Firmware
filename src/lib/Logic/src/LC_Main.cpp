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
		Event evt = get_event();
		switch(char(evt)){
			case EVT_EXIT:
				LDBG << "EVT_EXIT" << std::endl;
				run_flag = false;
			break;

			case EVT_PRESS_UP:
			case EVT_PRESS_DOWN:
			case EVT_PRESS_ENTER:
			case EVT_PRESS_BACK:
				m_ui.process(evt);
			break;
		}

		callbacks.top()->run();
		m_ui.draw();
		if(callbacks.empty()) run_flag = false;
	}
}
