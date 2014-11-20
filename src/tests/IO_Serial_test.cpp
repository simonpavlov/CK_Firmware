#include <IO/IO.h>
#include <emul/emulator.h>

#include <SDL/SDL.h>

#include <iostream>

using namespace std;

int main(){
	// set_screen_res(640, 480);
	emul_init(NETWORK_INIT);

	while(1){

		Serial::handler_recv();
		Serial::handler_send();
		SDL_Delay(500);

		bool flag = Serial::avail_msg_recv();

		// cout << flag << endl;

		if(flag){

			Message *msg = Serial::get_message();

			cout << "New message {" << endl;
			cout << *msg << endl;
			cout << "}" << endl;

			// cout << "\ttype: " << hex << (int) msg->get_type() << endl;
			// cout << "\tsize: " << dec << msg->get_arr()->size() << endl;
			// cout << "\tcrc16: " << hex << msg->get_crc16() << endl;
			// cout << "\tdata: ";
			// for(int i = 0; i < msg->get_arr()->size(); cout << " " << hex << (int)*(msg->get_arr()->data() + i++));
			// cout << endl << "}" << endl;

			Serial::put_message(msg);
		}

		
	}

	return 0;
}
