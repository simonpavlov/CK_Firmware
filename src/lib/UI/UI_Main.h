#ifndef UI_MAIN
#define UI_MAIN

#include "UI_Box.h"
#include "UI_Surface.h"
#include "UI_Font.h"
#include <emul/emulator.h>

// Realization in src/UI_Main.cpp

class Box;

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
class UI: public Surface{
	private:
		Box		*m_box;

		Font	default_font;
		bool	need_refresh;

	public:
		UI(Font font);
		~UI();

		Box *	push(Box *task);
		Box *	pop();
		Box *	get_box() {return m_box;} 

		// Возвращает шрифт "по умолчанию"
		Font &get_default_font() {return default_font;};

		// Обработка события
		bool process(Event evt);

	//+++++ Может быть сделать закрытыми
		// Обработать нажатие вверх
		void up();

		// Обработать нажатие вниз
		void down();

		// Обработать нажатие ввод
		void select();

		// Обработать нажатие назад
		void back();
	//-----

		// Отрисовка поьзовательского интерфейса
		void draw();

		// Очищает видео буфер
		// void clear_scr();
};

#endif //UI_MAIN
