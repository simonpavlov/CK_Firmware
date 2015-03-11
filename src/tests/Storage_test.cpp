#include <Storage/Storage.h>
#include <IO/CK_PasswordPair.h>
#include <IO/CK_Logger.h>
#include <emul/emulator.h>
#include <iostream>
#include <vector>
#include <string>

using namespace std;

//#define WRITE_TEST_PP
//#define READ_TEST_PP
//#define REMOVE_TEST_PP
#define PP_LIST_TEST

int main(){
	emul_init(STORAGE_SYS);

	Logger::set_output(&cout);

	DBG << "Trying Storage()" << endl;
	Storage stor;
	if(stor.get_health())
		DBG << "OK" << std::endl;
	else
		DBG << "FAIL" << std::endl;

	#ifdef WRITE_TEST_PP
	PasswordPair pp1("name2", "password");
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

	#ifdef PP_LIST_TEST
	vector<string> strs;
	strs = stor.get_pp_list();
	for(unsigned long i = 0; i < strs.size(); i++)
		cout << i + 1 << ": " << strs[i] << std::endl; 
	#endif

	emul_quit(NETWORK_SYS);

	return 0;
}
