#include "../LC_MainTask.h"

#include <Logic/LC_MessageTask.h>
#include <IO/CK_Logger.h>

#define DEBUG_LC_MAINTASK 1
#define LDBG DEBUG_LC_MAINTASK && DBG

MainTask::MainTask():
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

MainTask::~MainTask(){
	delete m_select_box;
	restore_box();
}

Task::RunCode MainTask::run(){
	if(m_select_box->get_stat() == Box::RUNNING){
		return NONE;
	}

	size_t res = m_select_box->get_res();

	if(res == 2){
		m_new_task = new MessageTask(":-)");
		return HAVE_CHILD;
	}
	else if(res == 3){
		LDBG << "MainTask done" << std::endl;
		return COMPLITED;
	}

	return NONE;
}
