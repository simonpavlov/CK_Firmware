#ifndef IO_DEVICEINFO
#define IO_DEVICEINFO

#include <stdint.h>

#include "IO_Message.h"
#include "IO_ByteStream.h"

class DeviceInfo {
	private:
		// Unical identifier
		uint64_t ident;
		// Battery state in percents
		uint8_t  batteryState;
		// Avaliable flash space in bytes
		uint32_t freeSpace;
	public:
		DeviceInfo();

		void refresh();
		Message * serialize();

		friend OByteStream & operator<<(OByteStream &stream, const DeviceInfo &dev_inf);
};

#endif //IO_DEVICEINFO
