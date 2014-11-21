#ifndef CK_LOGER
#define CK_LOGER

#include <sstream>

class Loger{
	private:
		static std::ostringstream warning_stream;
		static std::ostringstream debug_stream;

		static std::string get_time();
		static std::ostringstream & my_warning();
		static std::ostringstream & my_debug();

	public:
		static void flush();
		static void flush_warning();
		static void flush_debug();

		inline static std::ostringstream & Warning(){
			return my_warning();
		}

		inline static std::ostringstream & Debug(){
			my_debug() << "line: " << __LINE__ << " file: \"" << __FILE__ << "\" ";
			return my_debug();
		}

};

#endif //CK_LOGER
