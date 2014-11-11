#include "../IO_Serial.h"
#include <emul/emulator.h>

#include <cassert>
#include <stdint.h>

// #define DEBUG_IO_SERIAL
#include <iostream>

std::queue<Message *> Serial::queue_send;
std::queue<Message *> Serial::queue_recv;

void Serial::handler_recv(){
	#ifdef DEBUG_IO_SERIAL
	// std::cout << "IN Serial::handler_recv()" << std::endl;
	#endif

	uint8_t m_type;
	if(comm_recv(&m_type, sizeof(uint8_t)) != sizeof(uint8_t)){
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

		uint32_t	size;
		uint16_t	crc16;
		uint8_t		*data;

		if(comm_recv((uint8_t *)&size, sizeof(uint32_t)) != sizeof(uint32_t)){
			std::cerr << "Cant recv message size!" << std::endl;
			return;
		}

		#ifdef DEBUG_IO_SERIAL
		std::cout << "\tsize: " << size << std::endl;
		#endif

		data = new uint8_t[size];
		if(comm_recv(data, size) != size){
			std::cerr << "Cant recv message data!" << std::endl;
			return;
		}

		// crc16 = 0;
		// TODO: CRC16
		if(comm_recv((uint8_t *)&crc16, sizeof(uint16_t)) != sizeof(uint16_t))
			return;

		Message *msg = new Message(m_type, size, data, crc16);

		if(msg->check()){
			#ifdef DEBUG_IO_SERIAL
			std::cout << "\tSuccessful reception" << std::endl;
			#endif
			
			queue_recv.push(msg);
		}
		else{
			std::cerr << "Data is corupted!" << std::endl;
		}
	}
}

void Serial::handler_send(){
	#ifdef DEBUG_IO_SERIAL
	// std::cout << "IN Serial::handler_send()" << std::endl;
	#endif

	if(queue_send.empty()){
		return;
	}

	Message *msg = queue_send.front();
	queue_send.pop();

	uint8_t	m_type		= msg->get_type();
	uint16_t size		= msg->get_size();
	const uint8_t *data	= msg->get_data();
	uint16_t crc16		= msg->get_crc16();

	if(comm_send(&m_type, sizeof(uint8_t)) != sizeof(uint8_t)){
		std::cerr << "Cant send message type!" << std::endl;
		return;
	}

	if(comm_send((uint8_t *)&size, sizeof(uint32_t)) != sizeof(uint32_t)){
		std::cerr << "Cant send message size!" << std::endl;
		return;
	}

	if(comm_send(data, size) != (data, size)){
		std::cerr << "Cant send message data!" << std::endl;
		return;
	}

	if(comm_send((uint8_t *)&crc16, sizeof(uint16_t))){
		std::cerr << "Cant send crc16!" << std::endl;
		return;
	}
}

Message * Serial::get_message(){
	if(queue_recv.empty()){
		return NULL;
	}

	Message *res_msg = queue_recv.front();
	queue_recv.pop();
	return res_msg;
}