#ifndef LC_MAINTASK
#define LC_MAINTASK

#include <Logic/LC_Task.h>

// Realization in src/LC_MainTask.cpp

class MainTask: public Task{
	private:
		SelectBox	*m_select_box;
		Task		*m_new_task;

	public:
		MainTask();
		~MainTask();

		RunCode run();
		Task	*pop_task(){Task *task = m_new_task; m_new_task = NULL; return task;}
};

#endif //LC_MAINTASK
