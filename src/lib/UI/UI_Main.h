#ifndef UI_MAIN
#define UI_MAIN

#include <stack>

#include "UI_Task.h"
#include "UI_Surface.h"
#include "UI_Font.h"
#include <emul/emulator.h>

// Realization in src/UI_Main.cpp

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
//TODO: логично будет сделать этот класс static
class UI: public std::stack <Task*>, public Surface{
	public:
		//TODO constructor
		UI(Font &font);
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

		// Обработать нажатие назад
		void back();

		// Отрисовка поьзовательского интерфейса
		void draw();

		// Очищает видео буфер
		// void clear_scr();

	private:
		Font default_font;
		bool need_refresh;
};

#endif //UI_MAIN
