#include "../LC_App.h"

#include <IO/CK_Logger.h>
#include <emul/emulator.h>
#include <IO/CK_Logger.h>
#include <Uni3_Terminus20x10_psf.h>

#include <iostream>
#include <vector>
#include <string>

#define DEBUG_LOGIC 1
#define LDBG DEBUG_LOGIC && DBG

App::App():
	m_stor(),
	m_ui(Font(Uni3_Terminus20x10_psf)),
	m_tm(m_ui, m_stor)
{
	// Logger initialization
	Logger::set_output(&std::cout);
	LDBG << "IN App::App()" << std::endl;

	// Это можно засунуть в конструктор UI
	Box::init_Boxis(m_ui);

	m_tm.push(new MainListTask());
}

App::~App(){
	LDBG << "IN App::~App()" << std::endl;
}

void App::loop(){
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

		m_tm.run();

		if(m_tm.empty()){
			run_flag = false;
			continue;
		}

		m_ui.draw();
	}
}
