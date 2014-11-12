#include <iostream>
#include <IO/IO.h>

using namespace std;

int main(){
	uint16_t buf[] = {10, 0, 'l', 'o', 'g', 'i', 'n', 16, 0, 'p', 'a', 's', 's', 'w', 'o', 'r', 'd'};

	Message *msg = new Message(MessageType::PasswordPut, 34, (uint8_t *)buf);
	cout << "1: +" << endl;

	CK_String str;

	str = CK_String((uint8_t *)buf);

	cout << "Message: " << *msg << endl;
	cout << "2: +" << endl;

	PasswordPair pp(msg);
	cout << "3: +" << endl;

	delete msg;

	cout << "login: " << pp.login << endl
		<< "password: " << pp.password << endl;
	cout << "4: +" << endl;

	PasswordPair pp1(pp.login, pp.password);
	msg = pp1.to_message();

	cout << *msg << endl;

	delete msg;

	return 0;
}