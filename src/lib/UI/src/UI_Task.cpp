// #include "../UI_Main.h"
#include "../UI_Task.h"

Task::Task(UI &ui, Callback *cb): my_UI(ui) {
	my_UI.push(this);
	callback = cb;
}

void Task::suicide() {
	Task *task = my_UI.top();
	my_UI.pop();
	delete task;
}
