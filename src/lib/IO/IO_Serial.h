#ifndef IO_SERIAL
#define IO_SERIAL

#include <queue>
#include "IO_Message.h"

/*
	Реализация работы с последавательным портом
 */
/*
	Справка по queue:
	empty	- Test whether container is empty (public member function )
	size	- Return size (public member function )
	front	- Access next element (public member function )
	back	- Access last element (public member function )
	push	- Insert element (public member function )
	emplace	- Construct and insert element (public member function )
	pop		- Remove next element (public member function )
	swap	- Swap contents (public member function )
 */
class Serial{
	public:
		static void			handler_recv();
		static void			handler_send();
		static Message *	get_message(); // {return queue_recv.front();}
		static void			put_message(Message *msg) {queue_send.push(msg);}
		static bool			avail_msg_recv() {return !queue_recv.empty();}
	private:
		static std::queue<Message *> queue_send; //Очередь отправляемых
		static std::queue<Message *> queue_recv; //Очередь принятых
};

#endif //IO_SERIAL
