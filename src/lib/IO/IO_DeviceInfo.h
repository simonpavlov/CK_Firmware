#ifndef IO_DEVICEINFO
#define IO_DEVICEINFO

#include <stdint.h>

#include "IO_Message.h"

class DeviceInfo {
	private:
		// Unical identifier
		static uint64_t ident;
		// Battery state in percents
		static uint8_t  batteryState;
		// Avaliable flash space in bytes
		static uint32_t freeSpace;
	public:
		static void refresh();
		static Message * serialize();
};

#endif //IO_DEVICEINFO
