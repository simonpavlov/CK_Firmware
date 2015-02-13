#ifndef UI_TASK
#define UI_TASK

#include "UI_Surface.h"

// Realization in src/UI_Task.cpp

/*
	Базовая задача
*/
class Task {
	public:
		enum result {none, surf_changed, complite};

		virtual ~Task() {};

		virtual result	up() = 0;
		virtual result	down() = 0;
		virtual result 	select() = 0;
		virtual result	back() = 0;
		virtual Surface	& draw() = 0;
};

#endif //UI_TASK
