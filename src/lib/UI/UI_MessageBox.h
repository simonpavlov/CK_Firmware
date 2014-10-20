#ifndef UI_MESSAGEBOX
#define UI_MESSAGEBOX

#include <string>

#include "UI_Task.h"
#include "UI_Main.h"
#include "UI_Font.h"

/*
	Класс реализующий задачу отображения информации
*/
class MessageBox: public Task{
	private:
		std::string message;
		Surface *surf;
		Font &font;

		unsigned int max_height, max_width;

	public:
		// Единственный параметр - отображаемая информация
		MessageBox(UI &stk, std::string str);
		~MessageBox();

		void 	up(){};
		void	down(){};
		void	select(){suicide();};
		Surface	& draw();
};

#endif //UI_MESSAGEBOX
