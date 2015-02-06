#include <cstring>
#include "../Storage.h"
#include "../ff.h"

Storage::Storage(){
	f_mount(&m_fs, "", 0);
}

Storage::~Storage(){
	f_mount(NULL, "", 0);
	
	/*
	DIR dir;
	memset(&dir, 0, sizeof(dir));
	f_opendir(&dir, "");
	*/

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
