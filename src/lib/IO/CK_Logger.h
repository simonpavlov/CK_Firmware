#ifndef CK_LOGGER
#define CK_LOGGER

#include <sstream>
#include <iostream>

// Realization in src/CK_Logger.cpp

#define DBG Logger(__LINE__).debug()

class Logger{
	private:
		static std::ostream	*output;	
		static std::string	get_time();

	public:
		static void set_output(std::ostream *stream);

		Logger(int line);
		std::ostream & debug();
};

#endif //CK_LOGGER
