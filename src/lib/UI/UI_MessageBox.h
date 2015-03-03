#ifndef UI_MESSAGEBOX
#define UI_MESSAGEBOX

#include <string>

#include "UI_Box.h"
#include "UI_Font.h"
#include "UI_Main.h"

// Realization in src/UI_MessageBox.cpp

class UI;

/*
	Класс реализующий задачу отображения информации
*/
class MessageBox: public Box{
	public:
		// Единственный параметр - отображаемая информация
		MessageBox(std::string str);
		~MessageBox();

		Status 	up(){return m_stat = none;}
		Status	down(){return m_stat = none;}
		Status	select();
		Status	back(){return m_stat = none;}
		Surface	& draw();

	private:
		std::string message;
		Surface *surf;
};

#endif //UI_MESSAGEBOX
