#ifndef TEST_TASK
#define TEST_TASK

#include "UI_Task.h"
#include "UI_Main.h"
#include "UI_Font.h"

class test_task: public Task{
		int 	X, Y;
		Surface	surf;
		Font	&font;

	public:
		test_task(UI &stk, int x = 0, int y = 0, Callback *cb = NULL);
		~test_task();

		bool 	up();
		bool	down();
		bool	select();
		Surface	& draw();
};

#endif //TEST_TASK
