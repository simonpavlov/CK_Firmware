#ifndef TEST_TASK
#define TEST_TASK

#include "UI_Task.h"
#include "UI_Main.h"
#include "UI_Surface.h"

class test_task: public Task{
		int X;
	public:
		test_task(UI &stk, int x = 0);
		~test_task();

		void 	up();
		void	down();
		void	select();
		Surface	& draw();
};

#endif //TEST_TASK
