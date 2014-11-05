#include <IO/IO.h>
#include <emul/emulator.h>

int main(){
	emul_init(NETWORK_INIT);

	Serial::handler_recv();
	Serial::handler_send();

	while(1);

	return 0;
}
