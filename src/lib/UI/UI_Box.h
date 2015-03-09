#ifndef UI_TASK
#define UI_TASK

#include "UI_Surface.h"
#include <UI/UI_Main.h>

// Realization in src/UI_Box.cpp

class UI;

/*
	Базовая задача
*/
class Box {
	public:
		enum Status {RUNNING, HAVE_RESULT};

		static void init_Boxis(UI &ui) {o_ui = &ui;}
		
		Box(): m_stat(RUNNING) {}
		virtual ~Box() {};

		virtual bool	up() = 0;
		virtual bool	down() = 0;
		virtual bool 	select() = 0;
		virtual bool	back() = 0;
		virtual Surface	& draw() = 0;

		Status			get_stat() {return m_stat;}

	protected:
		static UI	*o_ui;

		Status		m_stat;
};

#endif //UI_TASK
