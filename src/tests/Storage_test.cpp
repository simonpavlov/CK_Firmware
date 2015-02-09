#include <Storage/Storage.h>
#include <IO/CK_PasswordPair.h>
#include <IO/CK_Logger.h>
#include <emul/emulator.h>
#include <iostream>

using namespace std;


int main(){
	emul_init(STORAGE_INIT);
	Logger::set_output(&cout);

	DBG << "Trying Storage()" << endl;
	Storage stor;
	if(stor.get_health())
		DBG << "OK" << std::endl;
	else
		DBG << "FAIL" << std::endl;

	PasswordPair pp("name", "password");
	DBG << "Trying stor.save()" << std::endl;
	if(stor.save(pp))
		DBG << "OK" << std::endl;
	else
		DBG << "FAIL" << std::endl;

	return 0;
}
