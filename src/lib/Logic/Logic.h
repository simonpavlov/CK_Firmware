#ifndef LOGIC
#define LOGIC

#include <Logic/LC_Callback.h>
#include <Storage/Storage.h>
#include <UI/UI.h>

//Realization in src/Logic.cpp

class Callback;

class Logic{
	private:
		Storage				m_stor;
		UI					m_ui;
		Callback			*callback;

	public:
		Logic();
		~Logic();

		void loop();

		friend class select_callback;
};


#endif //LOGIC
