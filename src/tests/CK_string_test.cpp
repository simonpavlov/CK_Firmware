#include <IO/CK_String.h>
#include <stdint.h>
#include <iostream>

using namespace std;

int main(){

	uint16_t buf[] = {10, 0, 'a', 'b', 'c', 'd', 'e'};

	CK_String *str_a = new CK_String((uint8_t *)buf);
	CK_String str_b = *str_a;
	CK_String str_c = str_b;
	str_c = *str_a;

	cout << "str_a: " << *str_a << endl
		<< "str_b: " << str_b << endl
		<< "str_c: " << str_c << endl;

	delete str_a;
	cout << "str_a deleted" << endl;

	cout << "str_b: " << str_b << endl;

	return 0;
}
