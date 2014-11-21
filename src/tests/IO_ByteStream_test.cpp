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

	String	str_l("login"),
			str_p("password");

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