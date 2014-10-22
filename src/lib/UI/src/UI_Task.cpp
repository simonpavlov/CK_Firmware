// #include "../UI_Main.h"
#include "../UI_Task.h"

Task::Task(UI &ui): my_UI(ui) {
	my_UI.push(this);
}

void Task::suicide() {
	// FIXME: valgrind отлавливает в следующей строке баг, 
	// причём только при первом вызове этой функции и
	// именно в этой функции, на работоспособность не влияет.

	Task *task = my_UI.top();
	my_UI.pop();
	delete task;
}
