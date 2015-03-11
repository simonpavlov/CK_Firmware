#include "../LC_MessageTask.h"
#include <IO/CK_Logger.h>

#define DEBUG_LC_MESSAGETASK 1
#define LDBG DEBUG_LC_MESSAGETASK && DBG

MessageTask::MessageTask(std::string str){
	m_message_box = new MessageBox(str);
	o_ui->push(m_message_box);
}

MessageTask::~MessageTask(){
	delete m_message_box;
	restore_box();
}

Task::RunCode MessageTask::run(){
	if(m_message_box->get_stat() == Box::RUNNING){
		return NONE;
	}

	LDBG << "MessageTask done" << std::endl;

	return COMPLITED;
}
