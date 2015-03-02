#ifndef LOGIC
#define LOGIC

#include <Logic/LC_Callback.h>
#include <Storage/Storage.h>
#include <UI/UI.h>
#include <stack>

//Realization in src/Logic.cpp

class Callback;

class Logic{
	private:
		Storage					m_stor;
		UI						m_ui;
		std::stack<Callback*>	callbacks;

	public:
		Logic();
		~Logic();

		void loop();

		friend class main_list;
		friend class message_callback;
};


#endif //LOGIC
