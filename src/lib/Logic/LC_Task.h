#ifndef LC_CALLBACK
#define LC_CALLBACK

#include <UI/UI.h>
#include <Storage/Storage.h>
#include <string>

// Realization in src/LC_Task.cpp

/*
 *	Класс-обстракция - основная единица Logic.
 *	Этот класс позволяет, наследуясь от него и перегружая метод run(),
 *	создавать задачи способные содержаться в TaskManager и общаться с ним,
 *	при этом выполняя собственный код.
 */
class Task{
	private:
		Box	*m_prev_box;

	protected:
		static UI		*o_ui;
		static Storage	*o_stor;

		// (!) Эта функция обязательно вызывается в деструкторе наследника.
		// Она восстанавливает предидущий Box.
		void restore_box(){o_ui->push(m_prev_box);}

	public:
		// Коды - результаты выполнения метода run()
		enum RunCode   {NONE,			// ничего особенного не поизошло
						HAVE_CHILD,		// имеется (1)задача-ребёнок
						HAVE_SUCCESSOR,	// имеется (2)задача-наследник
						COMPLITED		// задача завершина
					   };
		// (1) задача-ребёнок кладётся в стек TaskManager-а поверх текущей
		// (2) задача-наследник замещает текущую задачу

		// Инициализация статических переменных
		static void		init_Tasks(UI &ui, Storage &stor) {o_ui = &ui; o_stor = &stor;}

		// В конструкторе запоминается текущий Box
		Task(){m_prev_box = o_ui->get_box();}

		// В деструкторе Task должен обязательно восстановить предидущий Box
		virtual			~Task(){};

		// Сам run()
		virtual RunCode	run()	= 0;

		// Метод возвращающий сгенерированную задачу
		// (!) Владельцом задач считается TaskManager
		virtual Task	*pop_task(){return NULL;};
};

#endif //LC_CALLBACK
