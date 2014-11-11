#include <iostream>
#include <emul/emulator.h>
#include <IO/IO.h>

using namespace std;

int main(){

	emul_init(NETWORK_INIT);

	while(1){
		Serial::handler_recv();
		Serial::handler_send();
		SDL_Delay(100);

		if(Serial::avail_msg_recv()){

			Message *msg = Serial::get_message();

			cout << "Message: " << *msg << endl;

			PasswordPair pp(msg);

			cout << "login: " << pp.login << endl
				<< "password: " << pp.password << endl;

			delete msg;

			msg = new Message(MessageType::PasswordPut, ~0, NULL);
			cout << "msg: " << *msg << endl;

			Serial::put_message(msg);
		}
	}

	return 0;
}