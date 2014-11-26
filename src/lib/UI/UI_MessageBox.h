#ifndef UI_MESSAGEBOX
#define UI_MESSAGEBOX

#include <string>

#include "UI_Task.h"
#include "UI_Font.h"

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

		bool 	up(){return false;}
		bool	down(){return false;}
		bool	select();
		bool	back(){return false;}
		Surface	& draw();

	private:
		Callback *m_callback;

		std::string message;
		Surface *surf;
};

#endif //UI_MESSAGEBOX
