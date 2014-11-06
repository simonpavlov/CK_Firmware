#include <IO/IO.h>
#include <emul/emulator.h>

#include <SDL/SDL.h>

#include <iostream>
#include <errno.h>

using namespace std;

int main(){
	emul_init(NETWORK_INIT);

	while(1){
		Serial::handler_recv();
		SDL_Delay(500);

		if(Serial::avail_msg_send()){
			Message *msg = Serial::get_message();
			cout << "New message {" << endl;
			cout << "\ttype: " << hex << (int) msg->get_type() << endl;
			cout << "\tsize: " << dec << msg->get_size() << endl;
			cout << "\tdata: ";
			for(int i = 0; i < msg->get_size(); cout << hex << (int)*(msg->get_data() + i++));
			cout << endl << "}" << endl;
		}
	}

	return 0;
}
