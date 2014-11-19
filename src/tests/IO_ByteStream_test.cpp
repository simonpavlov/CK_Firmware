#include <iostream>

#include <IO/IO.h>

using namespace std;

int main(){
	DeviceInfo dinf;
	dinf.refresh();

	Array oarr;
	oByteStream out(&oarr);

	uint16_t	buf_login[] = {10, 0, 'l', 'o', 'g', 'i', 'n'},
				buf_passwd[] = {16, 0, 'p', 'a', 's', 's', 'w', 'o', 'r', 'd'};

	String	str_l((uint8_t *)buf_login),
			str_p((uint8_t *)buf_passwd);

	PasswordPair pp(str_l, str_p);

	out << dinf << str_l << pp;

	cout << "oarr: " << oarr << endl;

	cout << "FINISH!!!" << endl;

	return 0;
}