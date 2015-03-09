#ifndef LC_APP
#define LC_APP

#include <Logic/LC_Task.h>
#include <Logic/LC_TaskManager.h>
#include <Storage/Storage.h>
#include <UI/UI.h>
#include <stack>

//Realization in src/LC_App.cpp

/*
 *	Этот класс служит для:
 *		1) хранения в себе структур основных ресурсов
 *		2) периодической передачи управления TaskManager и UI
 *
 */
class App{
	private:
		Storage			m_stor;
		UI				m_ui;
		TaskManager		m_tm;

	public:
		App();
		~App();

		// Основной цикл выполнения программы
		void loop();
};


#endif //LOGIC
