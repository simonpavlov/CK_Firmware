#ifndef LC_PASSWORDSTASK
#define LC_PASSWORDSTASK

#include <Logic/LC_Task.h>
#include <UI/UI_SelectBox.h>

#include <vector>
#include <string>

// Realization src/LC_PasswordsTask.cpp

class PasswordsActionTask;

class PasswordsTask: public Task{
	private:
		bool						m_need_update;
		SelectBox					*m_pswds_box;
		Task						*m_new_task;
		std::vector<std::string>	pswd_list;

	public:
		PasswordsTask();
		~PasswordsTask();

		RunCode	run();
		Task	*pop_task(){Task *task = m_new_task; m_new_task = NULL; return task;}

};

class PasswordsActionTask: public Task{
	private:
		SelectBox	*m_action_box;
		std::string	m_pswd_name;

	public:
		PasswordsActionTask(std::string pswd_name);
		~PasswordsActionTask();

		RunCode	run();
		Task	*pop_task(){return NULL;}
};

#endif //LC_PASSWORDSTASK
