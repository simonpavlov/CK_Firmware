#include "../Logic.h"

#include <emul/emulator.h>
#include <IO/CK_Logger.h>
#include <Uni3_Terminus20x10_psf.h>
#include <iostream>

#define DEBUG_LOGIC 1
#define LDBG DEBUG_LOGIC && DBG

Logic::Logic():
	m_stor(),
	m_font(Uni3_Terminus20x10_psf),
	m_ui(m_font)
{
	// Logger initialization
	Logger::set_output(&std::cout);

}

Logic::~Logic(){
	emul_quit();
}

void Logic::loop(){
}
