#include <IO/CK_Logger.h>
#include <iostream>

int main(){
	Logger::set_output(&std::cout);
	DBG << "OK" << std::endl;

	return 0;
}
