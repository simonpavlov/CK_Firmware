#include <Storage/Storage.h>
#include <IO/CK_Logger.h>
#include <emul/emulator.h>
#include <iostream>

using namespace std;


int main(){
	emul_init(STORAGE_INIT);
	Logger::set_output(&cout);

	DBG << "Trying Storage()" << endl;
	Storage stor;

	return 0;
}