#include <cstring>
#include <IO/CK_Logger.h>
#include <IO/IO_ByteStream.h>
#include <IO/CK_Array.h>
#include <iostream>
#include <emul/emulator.h>
#include "../Storage.h"
#include "../ff.h"

#define STORAGE_DEBUG 1
#define LDBG STORAGE_DEBUG && DBG

const char pass_dir_name[] = "psswds";

char * Storage::pp_to_file_name(char *str, PasswordPair &pp){

	uint32_t login_size = pp.login.size();

	uint32_t file_name_len = login_size + sizeof(pass_dir_name) + 1;

	memcpy(str, pass_dir_name, sizeof(pass_dir_name));
	str[sizeof(pass_dir_name) - 1] = '/';

	for(uint32_t i = 0; i < login_size; i++)
		str[i + sizeof(pass_dir_name)] = pp.login[i];
	str[file_name_len - 1] = 0;

	return str;
}

Storage::Storage(){
	Logger::set_output(&std::cout);
	LDBG << "IN Storage::Storage()" << std::endl;

	emul_init(STORAGE_SYS);

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
	LDBG << "IN Storage::~Storage()" << std::endl;

	f_mount(NULL, "", 0);
	emul_quit(STORAGE_SYS);
}

std::vector<std::string> Storage::get_pp_list(){
	LDBG << "IN Storage::get_pp_list()" << std::endl;

	std::vector<std::string>	list;

	if(!m_health){
		LDBG << "FAIL: Storage in not initialized" << std::endl;
		return std::vector<std::string>();
	}

	FRESULT						res;
	FILINFO						finf;
	DIR							dir;
	
	char						*fname;

	#if _USE_LFN
	char lfname[_MAX_LFN + 1];
	finf.lfname = lfname;
	finf.lfsize = sizeof(lfname);
	#endif

	res = f_opendir(&dir, pass_dir_name);
	if(res != FR_OK){
		LDBG << "FAIL: Storage is broken" << std::endl;
		m_health = false;
		return std::vector<std::string>();
	}

	while(true){
		res = f_readdir(&dir, &finf);
		if(res != FR_OK){
			LDBG << "FAIL: Storage is broken" << std::endl;
			m_health = false;
			return std::vector<std::string>();
		}
		if(finf.fname[0] == 0) break;
		if(	finf.fname[0] == '.' ||
			finf.fattrib & AM_DIR) continue;

		#if _USE_LFN
		fname = *finf.lfname ? finfo.lfname : finfo.fname;
		#else
		fname = finf.fname;
		#endif

		LDBG << "file: " << fname << std::endl;
		list.push_back(fname);
	}

	return list;
}

bool Storage::save(PasswordPair &pp){
	if(!m_health) return false;

	uint32_t	file_name_len;
	char		*file_name;
	FIL			file;
	FRESULT		err_code;

	uint32_t login_size = pp.login.size();

	file_name_len = login_size + sizeof(pass_dir_name) + 1;
	file_name = (char *) malloc(file_name_len);
	if(file_name == NULL){
		LDBG << "Can't malloc memory" << std::endl;
		return false;
	}

	pp_to_file_name(file_name, pp);

	LDBG << "Save file: " << file_name << std::endl;

	LDBG << "Trying create file " << file_name << std::endl; 
	err_code = f_open(&file, file_name, FA_CREATE_ALWAYS | FA_WRITE); 
	if(err_code != FR_OK){
		LDBG << "FAIL can't created file " << file_name << std::endl;
		return false;
	}
	LDBG << "OK file " << file_name << " created" << std::endl;

	LDBG << "Trying write pp" << std::endl;

	UINT br;

	//uint32_t login_size = pp.login.size();
	/*
	uint32_t login_buf_size = pp.login.buf_size();

	err_code = f_write(&file, &login_size, sizeof(login_size), &br);
	if(err_code != FR_OK || br < sizeof(login_size)){
		LDBG << "Cant write login_size" << std::endl;
		return false;
	}

	err_code = f_write(&file, &pp.login, login_buf_size, &br);
	if(err_code != FR_OK || br < login_buf_size){
		LDBG << "Can't write login" << std::endl;
		return false;
	}

	uint32_t password_buf_size = pp.password.size();
	uint32_t psswd_serial_buf_size = pp.password.buf_size();

	err_code = f_write(&file, &password_buf_size, sizeof(password_size), &br);
	if(err_code != FR_OK || br < sizeof(password_buf_size)){
		LDBG << "Cant write password_buf_size" << std::endl;
		return false;
	}

	err_code = f_write(&file, &pp.password, psswd_serial_buf_size, &br);
	if(err_code != FR_OK || br < psswd_serial_buf_size){
		LDBG << "Can't write password" << std::endl;
		return false;
	}
	*/

	Array		arr;
	OByteStream stream(&arr);
	stream << pp;

	err_code = f_write(&file, arr.data(), arr.size(), &br);
	if(err_code != FR_OK || br < arr.size()){
		LDBG << "Can't write pp" << std::endl;
		return false;
	}

	if(f_close(&file) != FR_OK){
		LDBG << "Can't close file " << file_name << std::endl;
		return false;
	}

	free(file_name);

	LDBG << "OK pp written" << std::endl;

	return true;
}

bool Storage::load(PasswordPair &pp){
	if(!m_health) return false;

	uint32_t	file_name_len;
	char		*file_name;
	FIL			file;
	FRESULT		err_code;

	uint32_t login_size = pp.login.size();

	file_name_len = login_size + sizeof(pass_dir_name) + 1;
	file_name = (char *) malloc(file_name_len);
	if(file_name == NULL){
		LDBG << "Can't malloc memory" << std::endl;
		return false;
	}

	pp_to_file_name(file_name, pp);

	LDBG << "Read file: " << file_name << std::endl;

	err_code = f_open(&file, file_name, FA_OPEN_EXISTING | FA_READ);
	if(err_code != FR_OK){
		LDBG << "FAIL can't open file " << file_name << std::endl;
		return false;
	}
	LDBG << "OK file " << file_name << " opend" << std::endl;

	LDBG << "Trying load pp" << std::endl;

	UINT br;

	//uint32_t login_size = pp.login.size();
	uint32_t login_buf_size = pp.login.buf_size();

	err_code = f_lseek(&file, sizeof(pp.login.size()) + login_buf_size);
	if(err_code != FR_OK || f_tell(&file) != sizeof(pp.login.size()) + login_buf_size){
		LDBG << "Can't seek password" << std::endl;
		return false;
	}

	uint8_t	*psswd_serial_buf;

	uint32_t password_buf_size;
	uint32_t psswd_serial_buf_size;

	err_code = f_read(&file, &password_buf_size, sizeof(pp.password.size()), &br);
	if(err_code != FR_OK || br < sizeof(pp.password.size())){
		LDBG << "Can't read password size" << std::endl;
		return false;
	}

	psswd_serial_buf_size = password_buf_size + sizeof(pp.password.size());

	psswd_serial_buf = (uint8_t *) new uint8_t[psswd_serial_buf_size];
	if(psswd_serial_buf == NULL){
		LDBG << "Can't malloc memory" << std::endl;
		return false;
	}

	f_lseek(&file, sizeof(pp.login.size()) + login_buf_size);

	err_code = f_read(&file, psswd_serial_buf, psswd_serial_buf_size, &br);
	if(err_code != FR_OK || br < psswd_serial_buf_size){
		LDBG << "Can't read password" << std::endl;
		return false;
	}

	Array		arr(psswd_serial_buf, psswd_serial_buf_size);
	IByteStream	stream(&arr);
	stream >> pp.password;

	free(file_name);

	LDBG << "OK pp readed" << std::endl;

	return true;
}

bool Storage::remove(PasswordPair &pp){
	if(!m_health) return false;

	uint32_t	file_name_len;
	char		*file_name;
	FRESULT		err_code;

	uint32_t login_size = pp.login.size();

	file_name_len = login_size + sizeof(pass_dir_name) + 1;
	file_name = (char *) malloc(file_name_len);
	if(file_name == NULL){
		LDBG << "Can't malloc memory" << std::endl;
		return false;
	}

	pp_to_file_name(file_name, pp);

	LDBG << "Delete file " << file_name << std::endl;

	err_code = f_unlink(file_name);
	if(err_code != FR_OK && err_code != FR_NO_FILE){
		LDBG << "Can't delete file" << file_name << std::endl;
		return false;
	}

	free(file_name);

	return true;
}
