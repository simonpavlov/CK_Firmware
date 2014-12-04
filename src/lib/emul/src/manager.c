#include "../manager.h"
#include <string.h>

InitStatus emul_init(unsigned char mask){
	if(mask & VIDEO_INIT)
		if(video_init())
			return VIDEO_ERROR;

	if(mask & NETWORK_INIT)
		if(network_init())
			return NETWORK_ERROR;

	if(mask & STORAGE_INIT)
		if(storage_init())
			return STORAGE_ERROR;

	if(mask & EEPROM_INIT)
		if(eeprom_init())
			return EEPROM_ERROR;

	return ALL_RIGHT;
}

void emul_quit(){
	video_quit();
}
