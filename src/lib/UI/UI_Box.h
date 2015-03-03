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
		enum Status {none, surf_changed, complite};

		static void init_Boxis(UI &ui) {o_ui = &ui;}
		
		Box(): m_stat(surf_changed) {}
		virtual ~Box() {};

		virtual Status	up() = 0;
		virtual Status	down() = 0;
		virtual Status 	select() = 0;
		virtual Status	back() = 0;
		virtual Surface	& draw() = 0;

		Status			get_stat() {return m_stat;}

	protected:
		static UI	*o_ui;

		Status		m_stat;
};

#endif //UI_TASK
