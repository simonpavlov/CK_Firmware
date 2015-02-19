#ifndef LOGIC
#define LOGIC

#include <Storage/Storage.h>
#include <UI/UI.h>

//Realization in src/Logic.cpp

class select_callback: public SelectBox::Callback{
	public:
		int res;
		void exec(int number){
			res = number;
		}
};

class message_callback: public MessageBox::Callback{
	public:
		void exec(){
		}
};

class Logic{
	private:
		Storage				m_stor;
		UI					m_ui;
		select_callback		cb_select;
		message_callback	cb_message;

	public:
		Logic();
		~Logic();

		void loop();
};


#endif //LOGIC
