#include "../IO_DeviceInfo.h"

uint64_t	DeviceInfo::ident;
uint8_t		DeviceInfo::batteryState;
uint32_t	DeviceInfo::freeSpace;

#ifdef DEBUG_IO_DEVICEINFO
#include <iostream>
#endif //DEBUG_IO_DEVICEINFO

void DeviceInfo::refresh(){
	//TODO: нормальный опрос состояний девайса
	ident = 0xFFFFFFFFFFFFFFFF;
	batteryState = 100;
	freeSpace = 0;
}

Message * DeviceInfo::serialize(){
	uint32_t data_len = sizeof(uint64_t) + sizeof(uint8_t) + sizeof(uint32_t);
	uint8_t *data = new uint8_t[data_len];
	uint8_t *buf_w = data;

	#ifdef DEBUG_IO_DEVICEINFO
		std::cout << "data_len: " << data_len << std::endl;
	#endif //DEBUG_IO_DEVICEINFO

	*((uint64_t *)buf_w) = ident;
	buf_w += sizeof(uint64_t);

	*((uint8_t *)buf_w) = batteryState;
	buf_w += sizeof(uint8_t);

	*((uint32_t *)buf_w) = freeSpace;
	buf_w += sizeof(uint32_t);

	#ifdef DEBUG_IO_DEVICEINFO
		std::cout << "pointer data: " << (int *) data << std::endl;
		for(int i = 0; i < data_len; std::cout << (int)data[i++] << " ");
		std::cout << std::endl;
	#endif //DEBUG_IO_DEVICEINFO

	return new Message(MessageType::DeviceInfo, data_len, data);
}