#include "../Logic.h"

#include <emul/emulator.h>
#include <IO/CK_Logger.h>
#include <iostream>

#define DEBUG_LOGIC 1
#define LDBG DEBUG_LOGIC && DBG

Logic::Logic(){
	Logger::set_output(&std::cout);
	set_screen_res(320, 240);
	emul_init(VIDEO_INIT | STORAGE_INIT | EEPROM_INIT);
}

Logic::~Logic(){
	emul_quit();
}

void Logic::loop(){
}
