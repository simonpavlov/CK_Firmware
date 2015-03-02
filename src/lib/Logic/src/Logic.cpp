#include "../Logic.h"

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

	select_callback *cb_select = new select_callback(this);

	std::vector<std::string> str_mass;

	str_mass.push_back("Passwords");
	str_mass.push_back("Settings");
	str_mass.push_back("About Crypto Key");
	str_mass.push_back("Exit");

	m_ui.push(new SelectBox(m_ui, str_mass, cb_select));

	callback = cb_select;
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
		callback->run();
		if(m_ui.empty()) run_flag = false;
	}

	delete callback;
}
