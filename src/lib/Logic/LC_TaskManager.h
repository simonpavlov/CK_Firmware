#ifndef LC_TASKMANAGER
#define LC_TASKMANAGER

#include <Logic/LC_Task.h>
#include <UI/UI_Main.h>
#include <Storage/Storage.h>
#include <stack>

// Realization in src/LC_TaskManager.cpp

/*
 * Следующий класс предназначен для менеджмента задач.
 *
 * Принцип работы:
 * 1) заталкиваем задачу
 * 2) переодически вызываем её исполнение
 * 3) если задача (1)завершает свою работу, выгружаем её
 * 4) если задача (1)порадила задачу-ребёнка, заталкиваем ребёнка
 * 5) если задача (1)порадила задачу-наследника, заменяем задачу
 *		на наследника
 *
 * (1) Результат работы задачи мы узнае по возвращаемому коду
 * (!) Владельцом задач считается сам менеджер
 */
class TaskManager: private std::stack<Task *>{
	public:	
		// Параметры в конструктор передаются для инициализации
		// статических членов класса Task
		TaskManager(UI &ui, Storage &stor) {Task::init_Tasks(ui, stor);}

		// Деструктор извлекает все задачи из стека
		// и убивает (delete) их
		~TaskManager();
		
		// Добавление задачи
		// TODO: сделать const Task *task
		void	push(Task *task);

		// Проверка на пустоту
		bool	empty(){return std::stack<Task *>::empty();}
		
		// Обработка верхней задачи
		void	run();
};

#endif //LC_TASKMANAGER
