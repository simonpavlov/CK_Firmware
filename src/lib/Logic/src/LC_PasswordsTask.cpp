#include "../LC_PasswordsTask.h"

#include <IO/CK_Logger.h>

#define DEBUG_LC_PASSWORDS_TASK 1
#define LDBG DEBUG_LC_PASSWORDS_TASK && DBG

PasswordsTask::PasswordsTask():
	m_need_update(false)
{
	LDBG << "IN PasswordsTask::PasswordsTask()" << std::endl;

	pswd_list = o_stor->get_pp_list();
	pswd_list.push_back("back");
	
	m_pswds_box = new SelectBox(pswd_list);

	o_ui->push(m_pswds_box);
}

PasswordsTask::~PasswordsTask(){
	LDBG << "IN PasswordsTask::~PasswordsTask()" << std::endl;
	delete m_pswds_box;

	restore_box();
}

Task::RunCode PasswordsTask::run(){
	if(m_need_update){
		m_need_update	= false;

		pswd_list		= o_stor->get_pp_list();
		pswd_list.push_back("back");

		delete m_pswds_box;
		m_pswds_box = new SelectBox(pswd_list);

		o_ui->pop();
		o_ui->push(m_pswds_box);

		return NONE;
	}

	if(m_pswds_box->get_stat() != Box::HAVE_RESULT){
		return NONE;
	}

	size_t res = m_pswds_box->get_res();

	if(res == pswd_list.size() - 1){
		return COMPLITED;
	}
	else{
		m_need_update	= true;
		m_new_task		= new PasswordsActionTask(pswd_list[res]);
		return HAVE_CHILD;
	}

	return NONE;
}

PasswordsActionTask::PasswordsActionTask(std::string pswd_name):
	m_pswd_name(pswd_name)
{
	LDBG << "IN PasswordsActionTask::PasswordsActionTask()" << std::endl;

	std::vector<std::string>	list_items;
	list_items.push_back("remove");
	list_items.push_back("back");

	m_action_box = new SelectBox(list_items);

	o_ui->push(m_action_box);
}

PasswordsActionTask::~PasswordsActionTask(){
	LDBG << "IN PasswordsActionTask::~PasswordsActionTask()" << std::endl;
	delete m_action_box;

	restore_box();
}

Task::RunCode PasswordsActionTask::run(){
	if(m_action_box->get_stat() != Box::HAVE_RESULT){
		return NONE;
	}

	size_t res = m_action_box->get_res();

	if(res == 0){
		PasswordPair pp(m_pswd_name);
		o_stor->remove(pp);
	}
	else if(res == 1){
		return COMPLITED;
	}

	return NONE;
}
