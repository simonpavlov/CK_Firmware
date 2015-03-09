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
	protected:
		static UI		*o_ui;
		static Storage	*o_stor;

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

		virtual			~Task(){};

		// Сам run()
		virtual RunCode	run()	= 0;

		// Метод возвращающий сгенерированную задачу
		// (!) Владельцом задач считается TaskManager
		virtual Task	*pop_task(){return NULL;};
};

class MainListTask: public Task{
	private:
		SelectBox	*m_select_box;
		Task		*m_new_task;

	public:
		MainListTask();
		~MainListTask();

		RunCode run();
		Task	*pop_task(){Task *task = m_new_task; m_new_task = NULL; return task;}
};

class MessageTask: public Task{
	private:
		MessageBox	*m_message_box;
		Box			*m_last_box;

	public:
		MessageTask(std::string str);
		~MessageTask();

		RunCode run();
};

#endif //LC_CALLBACK
