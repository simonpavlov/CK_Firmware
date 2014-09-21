#ifndef UI_CONTROL_FUNCS
#define UI_CONTROL_FUNCS

/*
	Набор управляющих функций
*/
struct UI_control_funcs{
	void (* draw)();
	void (* press_up)();
	void (* press_down)();
	void (* press_enter)();
};

typedef struct UI_control_funcs	UI_control_funcs;

#endif