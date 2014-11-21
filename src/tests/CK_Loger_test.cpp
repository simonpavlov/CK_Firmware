#include <IO/CK_Loger.h>

int main(){
	Loger::Debug() << "1" << "\n";
	Loger::flush_debug();

	Loger::Warning() << "HI" << "\n";
	Loger::flush_warning();

	Loger::Debug() << "2" << "3" << "\n";
	Loger::flush_debug();

	return 0;
}