#ifndef UI_TASK
#define UI_TASK

/*
	Базовая задача
*/
class Task {
	private:

	public:
		virtual void up() {};
		virtual void down() {};
		virtual void select() {};
		virtual void redraw() {};
};

#endif //UI_TASK
