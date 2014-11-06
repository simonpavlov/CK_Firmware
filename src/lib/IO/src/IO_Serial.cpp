#include "../IO_Serial.h"
#include <emul/emulator.h>

#include <cassert>
#include <stdint.h>

// #define DEBUG_IO_SERIAL
#ifdef DEBUG_IO_SERIAL
#include <iostream>
#endif

std::queue<Message *> Serial::queue_send;
std::queue<Message *> Serial::queue_recv;

void Serial::handler_recv(){
	#ifdef DEBUG_IO_SERIAL
	std::cout << "IN Serial::handler_recv()" << std::endl;
	#endif

	uint8_t m_type;
	if(comm_recv(&m_type, sizeof(uint8_t)) != sizeof(uint8_t)) {
		return;
	}

	#ifdef DEBUG_IO_SERIAL
	std::cout << "\tNEW MESSAGE!" << std::endl;
	#endif

	if(m_type == MessageType::DeviceInit){
		#ifdef DEBUG_IO_SERIAL
		std::cout << "\tDeviceInit request" << std::endl;
		#endif

		uint8_t msg = MessageType::DeviceInit;
		comm_send(&msg, sizeof(uint8_t));
	}
	else{
		#ifdef DEBUG_IO_SERIAL
		std::cout << "\ttype: " << m_type << std::endl;
		#endif

		uint16_t	size;
		uint16_t	crc16;
		uint8_t		*data;

		if(comm_recv((uint8_t *)&size, sizeof(uint16_t)) != sizeof(uint16_t))
			return;

		#ifdef DEBUG_IO_SERIAL
		std::cout << "\tsize: " << size << std::endl;
		#endif

		//TODO: CRC16
		// if(comm_recv(&crc16, sizeof(uint16_t)) != sizeof(uint16_t))
		// 	return;

		data = new uint8_t[size];
		if(comm_recv(data, size) != size)
			return;
		
		#ifdef DEBUG_IO_SERIAL
		std::cout << "\tSuccessful reception" << std::endl;
		#endif
		Message *msg = new Message(m_type, size, crc16, data);
		Serial::put_message(msg);
	}
}

void Serial::handler_send(){
	#ifdef DEBUG_IO_SERIAL
	std::cout << "IN Serial::handler_send()" << std::endl;
	#endif
}

Message * Serial::get_message(){
	if(queue_recv.empty()){
		return NULL;
	}

	Message *res_msg = queue_recv.front();
	queue_recv.pop();
	return res_msg;
}