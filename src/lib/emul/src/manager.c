#include "../manager.h"
#include <string.h>

unsigned char system_status = 0;

InitStatus emul_init(unsigned char mask){
	system_status = mask;

	if(system_status & VIDEO_INIT)
		if(video_init())
			return VIDEO_ERROR;

	if(system_status & NETWORK_INIT)
		if(network_init())
			return NETWORK_ERROR;

	if(system_status & STORAGE_INIT)
		if(storage_init())
			return STORAGE_ERROR;

	if(system_status & EEPROM_INIT)
		if(eeprom_init())
			return EEPROM_ERROR;

	return ALL_RIGHT;
}

void emul_quit(){
	if(system_status & VIDEO_INIT)
		video_quit();

	if(system_status & NETWORK_INIT)
		//network_quit();

	if(system_status & STORAGE_INIT)
		storage_quit();

	if(system_status & EEPROM_INIT)
		eeprom_quit();
}
