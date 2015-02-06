#ifndef STORAGE
#define STORAGE

#include <IO/CK_PasswordPair.h>
#include <Storage/ff.h>

class Storage{
	private:
		FATFS m_fs;

	public:
		Storage();
		~Storage();

		// Password managing
		bool save(PasswordPair &password);
		bool load(PasswordPair &password);
		bool remove(PasswordPair &password);
};

#endif // STORAGE
