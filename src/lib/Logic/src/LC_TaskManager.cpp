#include "../LC_TaskManager.h"

#include <IO/CK_Logger.h>

#define DEBUG_LC_TASKMANAGER 1
#define LDBG DEBUG_LC_TASKMANAGER && DBG 

TaskManager::~TaskManager(){
	LDBG << "IN TaskManager::~TaskManager()" << std::endl;
	while(!empty()){
		delete top();
		pop();
	}
}

void TaskManager::push(Task *task){
	LDBG << "IN TaskManager::push(const Task *task)" << std::endl;
	std::stack<Task *>::push(task);	
}

void TaskManager::run(){
	//LDBG << "IN TaskManager::run()" << std::endl;
	Task			*task;
	Task::RunCode	code;

	task = top();
	code = task->run();

	switch(char(code)){
		case Task::NONE:
			break;

		case Task::HAVE_CHILD:
			push(task->pop_task());
			break;

		case Task::HAVE_SUCCESSOR:{
			Task *old_task;
	
			old_task = task;
			task = task->pop_task();

			delete old_task;
			pop();

			push(task);

			break;
		}
		/* Альтернативный вариант (не заню какой лучше)
		case Task::HAVE_SUCCESSOR:
			task = task->pop_task();
			delete top();
			pop();
			push(task);
			break;
		*/

		case Task::COMPLITED:
			delete task;
			pop();
			break;

	}
}
