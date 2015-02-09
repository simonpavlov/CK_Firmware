#include <cstring>
#include <IO/CK_Logger.h>
#include <iostream>
#include "../Storage.h"
#include "../ff.h"

#define STORAGE_DEBUG 0
#define LDBG STORAGE_DEBUG && DBG

const char pass_dir_name[] = "psswds";

Storage::Storage(){
	Logger::set_output(&std::cout);

	m_health = false;

	FRESULT err_code;

	//memset(&m_fs, 0, sizeof(m_fs));
	LDBG << "Trying mount" << std::endl;
	err_code = f_mount(&m_fs, "", 1);
	if(err_code != FR_OK){
		LDBG << "Can't mount, error code: " << err_code << std::endl;

		if(err_code == FR_NO_FILESYSTEM){
			LDBG << "Trying make fs" << std::endl;
			if(f_mkfs("", 0, 512) != FR_OK){
				LDBG << "FAIL make fs" << std::endl; 
				return;
			}
			f_mount(&m_fs, "", 1);
			LDBG << "OK fs maked" << std::endl;
		}
		else{
			return;
		}
	}
	LDBG << "OK fs mounted" << std::endl;

	/*
	for(uint32_t i = 0; i < sizeof(m_fs); i++){
		std::cout << std::hex  << (unsigned int) ((char *)(&m_fs))[i] << " ";
	}
	std::cout << std::endl;
	*/

	DIR dir;
	memset(&dir, 0, sizeof(dir));

	LDBG << "Trying open dir " << pass_dir_name << std::endl;
	err_code = f_opendir(&dir, pass_dir_name);
	if(err_code != FR_OK){
		LDBG << "Can't open " << pass_dir_name << " dir, error code: " << err_code << std::endl;
		LDBG << "Trying create" << std::endl;

		if(f_mkdir(pass_dir_name) != FR_OK){
			LDBG << "FAIL make " << pass_dir_name << " dir" << std::endl;
			return;
		}
		LDBG << "OK dir " << pass_dir_name << " maked" << std::endl;
	}
	else{
		LDBG << "OK dir " << pass_dir_name << " exist" << std::endl;
	}

	m_health = true;
}

Storage::~Storage(){
	f_mount(NULL, "", 0);
}

bool Storage::save(PasswordPair &pp){
	if(!m_health) return false;

	uint32_t	file_name_len;
	char		*file_name;
	FIL			file;
	FRESULT		err_code;

	file_name_len = pp.login.size() + sizeof(pass_dir_name) + 1;
	file_name = (char *) malloc(file_name_len);

	memcpy(file_name, pass_dir_name, sizeof(pass_dir_name));
	file_name[sizeof(pass_dir_name) - 1] = '/';

	for(uint32_t i = 0; i < file_name_len; i++)
		file_name[i + sizeof(pass_dir_name)] = pp.login[i];
	file_name[file_name_len - 1] = 0;

	LDBG << "Save file name: " << file_name << std::endl;

	LDBG << "Trying open file " << file_name << std::endl; 
	err_code = f_open(&file, file_name, FA_CREATE_ALWAYS | FA_WRITE); 
	if(err_code != FR_OK){
		LDBG << "FAIL can't created file " << file_name << std::endl;
		return false;
	}
	LDBG << "OK file " << file_name << " opend" << std::endl;

	LDBG << "Trying write pp" << std::endl;

	UINT br;

	uint32_t login_size = pp.login.size();
	uint32_t login_buf_size = pp.login.buf_size();

	err_code = f_write(&file, &login_size, sizeof(login_size), &br);
	if(err_code != FR_OK || br != sizeof(login_size)){
		LDBG << "Cant write login_size" << std::endl;
		return false;
	}

	err_code = f_write(&file, &pp.login, login_buf_size, &br);
	if(err_code != FR_OK || br != login_buf_size){
		LDBG << "Can't write login" << std::endl;
		return false;
	}

	uint32_t password_size = pp.password.size();
	uint32_t password_buf_size = pp.password.buf_size();

	err_code = f_write(&file, &password_size, sizeof(password_size), &br);
	if(err_code != FR_OK || br != sizeof(password_size)){
		LDBG << "Cant write password_size" << std::endl;
		return false;
	}

	err_code = f_write(&file, &pp.password, password_buf_size, &br);
	if(err_code != FR_OK || br != password_buf_size){
		LDBG << "Can't write password" << std::endl;
		return false;
	}

	if(f_close(&file) != FR_OK){
		LDBG << "Can't close file " << file_name << std::endl;
		return false;
	}

	LDBG << "OK pp written" << std::endl;

	return true;
}

bool Storage::load(PasswordPair &pp){
	if(!m_health) return false;

	return true;
}

bool Storage::remove(PasswordPair &pp){
	if(!m_health) return false;

	return true;
}
