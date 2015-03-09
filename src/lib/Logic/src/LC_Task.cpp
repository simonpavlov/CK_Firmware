#include "../LC_Task.h"

#include <IO/CK_Logger.h>

#define DEBUG_LC_CALLBACK 1
#define LDBG DEBUG_LC_CALLBACK && DBG

UI		* Task::o_ui = NULL;
Storage	* Task::o_stor = NULL;

MainListTask::MainListTask():
	m_new_task(NULL)
{
	std::vector<std::string> str_mass;

	str_mass.push_back("Passwords");
	str_mass.push_back("Settings");
	str_mass.push_back("About Crypto Key");
	str_mass.push_back("Shutdown");

	m_select_box = new SelectBox(str_mass);
	o_ui->push(m_select_box);
}

MainListTask::~MainListTask(){
	delete m_select_box;
}

Task::RunCode MainListTask::run(){
	if(m_select_box->get_stat() == Box::RUNNING){
		return NONE;
	}

	size_t res = m_select_box->get_res();

	if(res == 2){
		m_new_task = new MessageTask(":-)");
		return HAVE_CHILD;
	}
	else if(res == 3){
		LDBG << "MainListTask done" << std::endl;
		return COMPLITED;
	}

	return NONE;
}

MessageTask::MessageTask(std::string str){
	m_message_box = new MessageBox(str);
	m_last_box = o_ui->push(m_message_box);
}

MessageTask::~MessageTask(){
	delete m_message_box;
	o_ui->push(m_last_box);
}

Task::RunCode MessageTask::run(){
	if(m_message_box->get_stat() == Box::RUNNING){
		return NONE;
	}

	LDBG << "MessageTask done" << std::endl;

	return COMPLITED;
}
