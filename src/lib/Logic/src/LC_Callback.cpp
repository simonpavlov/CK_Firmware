#include "../LC_Callback.h"

#include <IO/CK_Logger.h>

#define DEBUG_LC_CALLBACK 1
#define LDBG DEBUG_LC_CALLBACK && DBG

Logic *Callback::o_lc = NULL;

main_list::main_list():
	new_res(false)
{
	/*
	std::vector<std::string> str_mass;

	str_mass.push_back("Passwords");
	str_mass.push_back("Settings");
	str_mass.push_back("About Crypto Key");
	str_mass.push_back("Exit");

	o_lc->m_ui.push(new SelectBox(str_mass, this));
	*/
}

void main_list::run(){
	/*
	if(!new_res) return;
	LDBG << "new_res: " << new_res << " res: " << res << std::endl;

	new_res = false;

	if(res == 2){
		o_lc->callbacks.push(new message_callback(":-)"));
	}
	else if(res == 3){
		LDBG << "main_list done" << std::endl;
		o_lc->m_ui.pop();
		o_lc->callbacks.pop();
		delete this;
	}
	*/
}

message_callback::message_callback(std::string str){
	/*
	o_lc->m_ui.push(new MessageBox(str));
	*/
}

void message_callback::run(){
	/*
	if(new_res){
		LDBG << "message_callback done" << std::endl;
		o_lc->m_ui.pop();
		o_lc->callbacks.pop();
		delete this;
	}
	*/
}
