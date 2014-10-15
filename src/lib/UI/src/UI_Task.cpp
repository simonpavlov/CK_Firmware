// #include "../UI_Main.h"
#include "../UI_Task.h"

Task::Task(UI &ui) {
	my_UI = &ui;
}

void Task::suicide() {
	delete my_UI->top();
	my_UI->pop();
}
