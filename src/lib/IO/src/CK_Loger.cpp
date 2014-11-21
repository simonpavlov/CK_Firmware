#include "../CK_Loger.h"

#include <iostream>
#include <ctime>

std::ostringstream Loger::warning_stream;
std::ostringstream Loger::debug_stream;

std::string Loger::get_time(){
	time_t rawtime;
	struct tm * timeinfo;
	char buffer[10];

	time (&rawtime);
	timeinfo = localtime (&rawtime);

	strftime (buffer,10,"%T",timeinfo);
  	
	return std::string(buffer);
}

void Loger::flush(){
	flush_warning();
	flush_debug();
}

void Loger::flush_warning(){
	if(warning_stream.str().size()){
		std::cout << warning_stream.str();
		warning_stream.str(std::string(""));
	}
}
void Loger::flush_debug(){
	if(debug_stream.str().size()){
		std::cout << debug_stream.str();
		debug_stream.str(std::string(""));
	}
}

std::ostringstream & Loger::my_warning(){
	if(!warning_stream.str().size()){
		warning_stream << get_time() << " WARNIGN ";
	}

	return warning_stream;
}

std::ostringstream & Loger::my_debug(){
	if(!debug_stream.str().size()){
		debug_stream << get_time() << " DEBUG ";
	}

	return debug_stream;
}
