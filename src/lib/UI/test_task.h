#ifndef TEST_TASK
#define TEST_TASK

#include "UI_Box.h"
#include "UI_Main.h"
#include "UI_Font.h"

// Realization in src/test_task.cpp

class test_task: public Box{
	public:
		class Callback{
			public:
				virtual void exec(int x) = 0;
		};

		test_task(int x = 0, int y = 0, Callback *cb = NULL);
		~test_task();

		result 	up();
		result	down();
		result	select();
		result	back();
		Surface	& draw();

	private:
		Callback *m_callback;

		int 	X, Y;
		Surface	surf;
		Font	&font;
};

#endif //TEST_TASK
