#include "../CK_Logger.h"

#include <iostream>
#include <ctime>

std::ostream str(NULL);
std::ostream * Logger::output = &str;

std::string Logger::get_time(){
	time_t rawtime;
	struct tm * timeinfo;
	char buffer[10];

	time (&rawtime);
	timeinfo = localtime (&rawtime);

	strftime (buffer,10,"%T",timeinfo);
  	
	return std::string(buffer);
}

void Logger::set_output(std::ostream *stream){
	if(stream) output = stream;
	else{
		output = &str;
	}
}

Logger::Logger(int line){
	*output << "DEBUG " << get_time() << " line: " << line << " ";
}

std::ostream & Logger::debug(){
	return *output;
}
