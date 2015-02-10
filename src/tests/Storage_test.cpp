#include <Storage/Storage.h>
#include <IO/CK_PasswordPair.h>
#include <IO/CK_Logger.h>
#include <emul/emulator.h>
#include <iostream>

using namespace std;

#define WRITE_TEST_PP
#define READ_TEST_PP
#define REMOVE_TEST_PP

int main(){
	emul_init(STORAGE_INIT);
	atexit(emul_quit);

	Logger::set_output(&cout);

	DBG << "Trying Storage()" << endl;
	Storage stor;
	if(stor.get_health())
		DBG << "OK" << std::endl;
	else
		DBG << "FAIL" << std::endl;

	#ifdef WRITE_TEST_PP
	PasswordPair pp1("name", "password");
	DBG << "Trying stor.save()" << std::endl;
	if(stor.save(pp1))
		DBG << "OK" << std::endl;
	else
		DBG << "FAIL" << std::endl;
	#endif

	#ifdef READ_TEST_PP
	PasswordPair pp2("name", "");
	DBG << "Trying stor.load()" << std::endl;
	if(stor.load(pp2))
		DBG << "OK" << std::endl;
	else
		DBG << "FAIL" << std::endl;

	cout << "pp2.password: " << pp2.password << endl;
	#endif

	#ifdef REMOVE_TEST_PP
	PasswordPair pp3("name", "");
	DBG << "Trying stor.remove()" << std::endl;
	if(stor.remove(pp3))
		DBG << "OK" << std::endl;
	else
		DBG << "FAIL" << std::endl;
	#endif

	return 0;
}
