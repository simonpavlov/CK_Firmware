#include <iostream>
#include <emul/emulator.h>
#include <IO/IO.h>
#include <IO/CK_PasswordPair.h>
#include <IO/CK_String.h>

using namespace std;

int main(){

	emul_init(NETWORK_SYS);

	while(1){
		// cout << "***" << endl;

		Serial::handler_recv();
		Serial::handler_send();
		SDL_Delay(100);

		if(Serial::avail_msg_recv()){

			Message *msg = Serial::get_message();
			cout << "Message: " << *msg << endl;

			switch(msg->get_type()){
				case MessageType::DeviceInfo:{
					cout << "DeviceInfo" << endl;

					delete msg;

					DeviceInfo di;

					Array *o_arr = new Array();
					OByteStream output(o_arr);

					di.refresh();
					output << di;

					msg = new Message(MessageType::DeviceInfo, o_arr);

					cout << "msg: " << *msg << endl;

					Serial::put_message(msg);

					break;
				}
				case MessageType::PasswordPut:{
					cout << "PasswordPut" << endl;

					PasswordPair pp;
					Array *o_arr = new Array();

					IByteStream input(msg->get_arr());
					OByteStream output(o_arr);

					input >> pp;
					output << String();

					delete msg;
		
					cout << "login: " << pp.login << endl
						<< "password: " << pp.password << endl;
		
					msg = new Message(MessageType::PasswordPut, o_arr);
					cout << "msg: " << *msg << endl;

					Serial::put_message(msg);

					break;
				}
				case MessageType::PasswordGet:{
					cout << "PasswordGet" << endl;

					String login;
					PasswordPair pp(String("login"), String("password"));

					Array *o_arr = new Array();
					IByteStream input(msg->get_arr());
					OByteStream output(o_arr);

					input >> login;
					output << pp;

					delete msg;

					cout << "login: " << login << endl;

					msg = new Message(MessageType::PasswordGet, o_arr);
					cout << "msg: " << *msg << endl;

					Serial::put_message(msg);

					break;
				}
				case MessageType::TextEncrypt:{
					cout << "TextEncrypt" << endl;

					String str;

					Array *o_arr = new Array();
					IByteStream input(msg->get_arr());
					OByteStream output(o_arr);

					input >> str;
					cout << str << endl;;
					//Do something with str
					output << str;

					delete msg;

					msg = new Message(MessageType::TextEncrypt, o_arr);
					cout << "msg: " << *msg << endl;

					Serial::put_message(msg);

					break;
				}
				case MessageType::TextDecrypt:{
					cout << "TextDecrypt" << endl;

					String str;

					Array *o_arr = new Array();
					IByteStream input(msg->get_arr());
					OByteStream output(o_arr);

					input >> str;
					cout << str << endl;
					//Do something with str
					output << str;

					delete msg;

					msg = new Message(MessageType::TextDecrypt, o_arr);
					cout << "msg: " << *msg << endl;

					Serial::put_message(msg);

					break;
				}
				default:{
					cout << "Unknown Type!" << endl;
					break;
				}
			}
		}
	}

	emul_quit(NETWORK_SYS);

	return 0;
}
