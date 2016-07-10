#ifndef LC_MESSAGETASK
#define LC_MESSAGETASK

// Realization in src/LC_MessageTask.cpp

#include <Logic/LC_Task.h>
#include <UI/UI_MessageBox.h>

class MessageTask: public Task{
	private:
		MessageBox	*m_message_box;

	public:
		MessageTask(std::string str);
		~MessageTask();

		RunCode run();
};

#endif //LC_MESSAGETASK
