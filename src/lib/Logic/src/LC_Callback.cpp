#include "../LC_Callback.h"

#include <IO/CK_Logger.h>

#define DEBUG_LC_CALLBACK 1
#define LDBG DEBUG_LC_CALLBACK && DBG

Logic *Callback::o_lc = NULL;

main_list::main_list(){
	std::vector<std::string> str_mass;

	str_mass.push_back("Passwords");
	str_mass.push_back("Settings");
	str_mass.push_back("About Crypto Key");
	str_mass.push_back("Shutdown");

	m_select_box = new SelectBox(str_mass);
	o_lc->m_ui.push(m_select_box);
}

void main_list::run(){
	if(m_select_box->get_stat() != Box::complite){
		return;
	}

	size_t res = m_select_box->get_res();

	if(res == 2){
		o_lc->callbacks.push(new message_callback(":-)"));
	}
	else if(res == 3){
		LDBG << "main_list done" << std::endl;
		o_lc->m_ui.pop();
		o_lc->callbacks.pop();
		delete this;
	}
}

message_callback::message_callback(std::string str){
	m_message_box = new MessageBox(str);
	o_lc->m_ui.push(m_message_box);
}

void message_callback::run(){
	if(m_message_box->get_stat() != Box::complite){
		return;
	}

	LDBG << "message_callback done" << std::endl;
	o_lc->m_ui.pop();
	o_lc->callbacks.pop();
	delete this;
}
