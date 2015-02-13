#include "../manager.h"
#include <string.h>

#define DEBUG_MANAGER

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
	if(system_status & VIDEO_INIT){
		#ifdef DEBUG_MANAGER
		printf("video_quit()\n");
		video_quit();
		#endif
	}

	if(system_status & NETWORK_INIT){
		#ifdef DEBUG_MANAGER
		printf("network_quit()\n");
		//network_quit();
		#endif
	}

	if(system_status & STORAGE_INIT){
		#ifdef DEBUG_MANAGER
		printf("storage_quit()\n");
		storage_quit();
		#endif
	}

	if(system_status & EEPROM_INIT){
		#ifdef DEBUG_MANAGER
		printf("eeprom_quit()\n");
		eeprom_quit();
		#endif
	}
}
