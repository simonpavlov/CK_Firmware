#ifndef LOGIC
#define LOGIC

#include <Storage/Storage.h>
#include <UI/UI.h>

//Realization in src/Logic.cpp

class Logic{
	private:
		Storage	m_stor;
		Font	m_font;
		UI		m_ui;

	public:
		Logic();
		~Logic();

		void loop();
};


#endif //LOGIC
