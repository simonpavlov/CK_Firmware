#include <iostream>
#include <emul/emulator.h>
#include <IO/IO.h>

using namespace std;

int main(){

	emul_init(NETWORK_INIT);

	while(1){
		// cout << "***" << endl;

		Serial::handler_recv();
		Serial::handler_send();
		SDL_Delay(100);

		if(Serial::avail_msg_recv()){

			Message *msg = Serial::get_message();
			cout << "Message: " << *msg << endl;

			// switch(msg->get_type()){
			// 	case MessageType::PasswordPut:{
			// 		cout << "PasswordPair" << endl;

			// 		PasswordPair pp(msg);
			// 		delete msg;
		
			// 		cout << "login: " << pp.login << endl
			// 			<< "password: " << pp.password << endl;
		
			// 		msg = new Message(MessageType::PasswordPut, ~0, NULL);
			// 		cout << "msg: " << *msg << endl;

			// 		Serial::put_message(msg);

			// 		break;
			// 	}
			// 	case MessageType::DeviceInfo:{
			// 		cout << "DeviceInfo" << endl;

			// 		delete msg;

			// 		DeviceInfo di;
			// 		di.refresh();
			// 		msg = di.serialize();

			// 		cout << "msg: " << *msg << endl;

			// 		Serial::put_message(msg);

			// 		break;
			// 	}
			// 	case MessageType::PasswordGet:{
			// 		cout << "PasswordGet" << endl;

			// 		String login(msg->get_data());
			// 		delete msg;

			// 		cout << "login: " << login << endl;

			// 		uint16_t	buf_login[] = {10, 0, 'l', 'o', 'g', 'i', 'n'},
			// 					buf_passwd[] = {16, 0, 'p', 'a', 's', 's', 'w', 'o', 'r', 'd'};

			// 		PasswordPair pp(String((uint8_t *) buf_login), String((uint8_t *) buf_passwd));
			// 		msg = pp.to_message();
			// 		cout << *msg << endl;

			// 		Serial::put_message(msg);

			// 		break;
			// 	}
			// 	case MessageType::TextEncrypt:{
			// 		cout << "TextEncrypt" << endl;

			// 		break;
			// 	}
			// 	case MessageType::TextDecrypt:{
			// 		cout << "TextDecrypt" << endl;

			// 		break;
			// 	}
			// }
		}
	}

	return 0;
}