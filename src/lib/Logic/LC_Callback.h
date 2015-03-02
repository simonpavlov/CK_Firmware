#ifndef LC_CALLBACK
#define LC_CALLBACK

#include <Logic/Logic.h>
#include <UI/UI.h>

// Realization in src/LC_Callback.cpp

class Logic;

class Callback{
	public:
		virtual void run()	= 0;
		virtual ~Callback(){};
};

class select_callback: public SelectBox::Callback, public Callback{
	public:
		bool	new_res;
		int		res;
		Logic	*m_logic;

		select_callback(Logic *init_logic):
			new_res(false),
			m_logic(init_logic)
		{}

		void exec(int number){
			res		= number;
			new_res = true;
		}

		void run();
};

class message_callback: public MessageBox::Callback{
	public:
		void exec(){
		}
};

#endif //LC_CALLBACK
