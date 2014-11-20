#include <iostream>

#include <IO/IO.h>
#include <cstring>

using namespace std;

int main(){
	DeviceInfo dinf;
	dinf.refresh();

	Array oarr;
	// Array arr(20);

	OByteStream out(&oarr);
	IByteStream input(&oarr);

	uint16_t	buf_login[] = {10, 0, 'l', 'o', 'g', 'i', 'n'},
				buf_passwd[] = {16, 0, 'p', 'a', 's', 's', 'w', 'o', 'r', 'd'};

	String	str_l((uint8_t *)buf_login),
			str_p((uint8_t *)buf_passwd);

	PasswordPair pp(str_l, str_p), pp_free;

	out << pp << dinf;
	input >> pp_free;

	cout << "oarr: " << oarr << endl
		// << "arr: " << arr << endl
		<< "login: " << pp_free.login << endl
		<< "passwd: " << pp_free.password << endl;

	cout << "FINISH!!!" << endl;

	return 0;
}