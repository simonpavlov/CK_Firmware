#include <cstring>
#include <IO/CK_Logger.h>
#include <iostream>
#include "../Storage.h"
#include "../ff.h"

Storage::Storage(){
	Logger::set_output(&std::cout);

	DBG << "Trying mount" << std::endl;
	if(f_mount(&m_fs, "", 1) != FR_OK){
		DBG << "Can't mount" << std::endl;
	}

	DBG << "1" << std::endl;

	DIR *dir;
	dir = (DIR *) malloc(sizeof(dir));
	memset(dir, 0, sizeof(*dir));
	//if(f_opendir(dir, "") != FR_OK)
	DBG << "ERROR " << f_opendir(dir, "/one") << std::endl;
	DBG << "2" << std::endl;
}

Storage::~Storage(){
	f_mount(NULL, "", 0);
}

bool Storage::save(PasswordPair &password){

	return true;
}

bool Storage::load(PasswordPair &password){

	return true;
}

bool Storage::remove(PasswordPair &password){

	return true;
}
