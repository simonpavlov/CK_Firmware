#include "../IO_Serial.h"
#include <emul/emulator.h>

#include <cassert>
#include <stdint.h>

#define DEBUG_IO_SERIAL
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
		if(comm_recv((uint8_t *)&crc16, sizeof(uint16_t)) != sizeof(uint16_t)){
			std::cerr << "Cant recv message crc16!" << std::endl;
			return;
		}

		Message *msg = new Message(m_type, new Array(data, size), crc16);

		// if(msg->check()){
		if(true){
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
	uint32_t size		= msg->get_arr()->size();
	uint16_t crc16		= msg->get_crc16();

	uint32_t data_len = (size + 1)?
		sizeof(uint8_t) + sizeof(uint32_t) + msg->get_arr()->size() + sizeof(uint16_t):
		sizeof(uint8_t) + sizeof(uint32_t) + sizeof(uint16_t);

	uint8_t *data	= new uint8_t[data_len];
	uint8_t *buf_w = data;

	*buf_w++ = m_type;
	*((uint32_t *)buf_w) = size;
	buf_w += sizeof(size);

	uint8_t *buf_r = msg->get_arr()->data();
	for(uint32_t i = 0, i_max = (size + 1)? size: 0; i < i_max; i++) *buf_w++ = *buf_r++;

	*((uint16_t *)buf_w) = crc16;
	buf_w += sizeof(crc16);

	if(comm_send(data, data_len) != data_len){
		std::cerr << "Cant send message!" << std::endl;
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