#ifndef UI_MAIN
#define UI_MAIN

#include <stack>

#include "UI_Task.h"
#include "UI_Surface.h"
#include "UI_Font.h"
#include <emul/emulator.h>

class Task;

/*
	Этот класс реализует работу со стеком задач
*/
/*
	Справка по stack
	empty	- Test whether container is empty (public member function )
	size	- Return size (public member function )
	top		- Access next element (public member function )
	push	- Insert element (public member function )
	emplace	- Construct and insert element (public member function )
	pop		- Remove top element (public member function )
	swap	- Swap contents (public member function )
*/
class UI: public std::stack <Task*>, public Surface{
	public:
		enum state {unchanged, busy, changed};

		//TODO constructor
		UI(ScreenInfo &scr, Font &font);
		~UI();

		// Обёртка для stack::push()
		void push(Task *task);

		// Обёртка для stack::pop()
		void pop();

		// Возвращает шрифт "по умолчанию"
		Font &get_default_font() {return default_font;};

		// Обработать нажатие вверх
		void up();

		// Обработать нажатие вниз
		void down();

		// Обработать нажатие ввод
		void select();

		// Отрисовка поьзовательского интерфейса
		void draw();

		// Очищает видео буфер
		// void clear_scr();

		// Возвращает текущее состояние апаратного сурфейса
		state take_state(){return my_state; my_state = unchanged;}

	private:
		Font default_font;
		state my_state;
		bool need_refresh;
};

#endif //UI_MAIN
