// #include "../UI_Main.h"
#include "../UI_Task.h"

Task::Task(UI &ui): my_UI(ui) {}

void Task::suicide() {
	// FIXME: valgrind отлавливает в следующей строке баг, 
	// причём только при первом вызове этой функции и
	// именно в этой функции, на работоспособность не влияет.

	delete my_UI.top();
	my_UI.pop();
}
