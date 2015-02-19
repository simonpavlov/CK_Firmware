#ifndef STORAGE
#define STORAGE

#include <IO/CK_PasswordPair.h>
#include <Storage/ff.h>

// Realization in src/Storage.cpp

class Storage{
	private:
		FATFS	m_fs;
		bool	m_health;

		static char *	pp_to_file_name(char *str, PasswordPair &pp);

	public:
		Storage();
		~Storage();

		bool get_health(){return m_health;}

		// Password managing
		bool save(PasswordPair &password);
		bool load(PasswordPair &password);
		bool remove(PasswordPair &password);
};

#endif // STORAGE
