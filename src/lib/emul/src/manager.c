#include "../manager.h"
#include <string.h>

#define DEBUG_MANAGER

unsigned char system_status = 0;

InitStatus emul_init(unsigned char new_system_status){
	unsigned char delta_system_status;

	delta_system_status	= (system_status | new_system_status) ^ system_status;
	system_status		= system_status | delta_system_status;

	if(delta_system_status & VIDEO_SYS){
		#ifdef DEBUG_MANAGER
		printf("video_init()\n");
		#endif
		if(video_init())
			return VIDEO_ERROR;
	}

	if(delta_system_status & NETWORK_SYS){
		#ifdef DEBUG_MANAGER
		printf("network_init()\n");
		#endif
		if(network_init())
			return NETWORK_ERROR;
	}

	if(delta_system_status & STORAGE_SYS){
		#ifdef DEBUG_MANAGER
		printf("storage_init()\n");
		#endif
		if(storage_init())
			return STORAGE_ERROR;
	}


	if(delta_system_status & EEPROM_SYS){
		#ifdef DEBUG_MANAGER
		printf("eeprom_init()\n");
		#endif
		if(eeprom_init())
			return EEPROM_ERROR;
	}

	return ALL_RIGHT;
}

void emul_quit(unsigned char system_off){
	unsigned int delta_system_status;

	if(system_off){
		delta_system_status	= system_status & system_off;
		system_status		= ~delta_system_status & system_status;
	}
	else{
		delta_system_status	= ~0;
		system_status		= 0;
	}

	if(delta_system_status & VIDEO_SYS){
		#ifdef DEBUG_MANAGER
		printf("video_quit()\n");
		video_quit();
		#endif
	}

	if(delta_system_status & NETWORK_SYS){
		#ifdef DEBUG_MANAGER
		printf("network_quit()\n");
		//network_quit();
		#endif
	}

	if(delta_system_status & STORAGE_SYS){
		#ifdef DEBUG_MANAGER
		printf("storage_quit()\n");
		storage_quit();
		#endif
	}

	if(delta_system_status & EEPROM_SYS){
		#ifdef DEBUG_MANAGER
		printf("eeprom_quit()\n");
		eeprom_quit();
		#endif
	}
}
