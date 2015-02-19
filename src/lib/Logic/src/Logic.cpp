#include "../Logic.h"

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

	std::vector<std::string> str_mass;

	str_mass.push_back("Passwords");
	str_mass.push_back("Settings");
	str_mass.push_back("About Crypto Key");

	m_ui.push(new SelectBox(m_ui, str_mass, &cb_select));
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
				LDBG << "Res: " << cb_select.res << std::endl;
				if(cb_select.res == 2){
					m_ui.push(new MessageBox(m_ui, ":-)", &cb_message));
					cb_select.res = -1;
				}
				else{
					run_flag = false;
				}
			break;

			case EVT_PRESS_BACK:
				LDBG << "EVT_PRESS_BACK" << std::endl;
				m_ui.back();
			break;
		}

		m_ui.draw();
	}
}
