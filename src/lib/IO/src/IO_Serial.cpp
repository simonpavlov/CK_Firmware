#include "../IO_Serial.h"

#include <iostream>

#define DEBUG_IO_SERIAL

void Serial::handler_send(){
	#ifdef DEBUG_IO_SERIAL
	std::cout << "IN Serial::handler_send()" << std::endl;
	#endif
}

void Serial::handler_recv(){
	#ifdef DEBUG_IO_SERIAL
	std::cout << "IN Serial::handler_recv()" << std::endl;
	#endif
}