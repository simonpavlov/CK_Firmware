#ifndef LC_CALLBACK
#define LC_CALLBACK

#include <Logic/LC_Main.h>
#include <UI/UI.h>
#include <string>

// Realization in src/LC_Callback.cpp

class Logic;

class Callback{
	protected:
		static Logic *o_lc;

	public:
		static  void init_Callbacks(Logic *lc) {o_lc = lc;}
		virtual void run()	= 0;
		virtual ~Callback(){};
};

class main_list: public SelectBox::Callback, public Callback{
	private:
		bool	new_res;
		int		res;

	public:
		main_list();

		void exec(int number){
			res		= number;
			new_res = true;
		}

		void run();
};

class message_callback: public Callback{
	public:
		message_callback(std::string str);

		void run();
};

#endif //LC_CALLBACK
