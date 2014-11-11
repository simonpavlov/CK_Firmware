#include "../IO_Message.h"
#include <iostream>

const uint16_t Message::crc16_table[16] = {
	0x0000, 0x1081, 0x2102, 0x3183,
	0x4204, 0x5285, 0x6306, 0x7387,
	0x8408, 0x9489, 0xa50a, 0xb58b,
	0xc60c, 0xd68d, 0xe70e, 0xf78f
};

uint16_t Message::check_sum() const {

	uint32_t	len = size;
	uint16_t	crc = 0xffff;
	uint8_t		c;
	uint8_t		*p = (uint8_t *)data;

	while(len--){
		c = *p++;
		crc = ((crc >> 4) & 0x0fff) ^ crc16_table[((crc ^ c) & 15)];
		c >>= 4;
		crc = ((crc >> 4) & 0x0fff) ^ crc16_table[((crc ^ c) & 15)];
	}

	return ~crc & 0xffff;
}

bool Message::check() const {
	return check_sum() == crc16;
}

std::ostream & operator<<(std::ostream &stream, const Message &msg){
	stream << "{ ";
	stream << "type: 0x" << std::hex << (int) msg.type;
	stream << ", size: " << std::dec << msg.size;
	stream << ", crc16: 0x" << std::hex << msg.crc16;
	stream << ", data:";
	for(int i = 0; i < msg.size; stream << " 0x" << std::hex << (int)*(msg.data + i++));
	stream << " }";

	return stream;
}