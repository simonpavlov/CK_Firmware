#ifndef UI_MESSAGEBOX
#define UI_MESSAGEBOX

#include <string>

#include "UI_Task.h"
#include "UI_Font.h"
#include "UI_Main.h"

// Realization in src/UI_MessageBox.cpp

class UI;

/*
	Класс реализующий задачу отображения информации
*/
class MessageBox: public Task{
	public:
		class Callback{
			public:
				virtual void exec() = 0;
		};

		// Единственный параметр - отображаемая информация
		MessageBox(UI &init_ui, std::string str, Callback *cb = NULL);
		~MessageBox();

		result 	up(){return none;}
		result	down(){return none;}
		result	select();
		result	back(){return none;}
		Surface	& draw();

	private:
		Callback *m_callback;

		std::string message;
		Surface *surf;
};

#endif //UI_MESSAGEBOX
