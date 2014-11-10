#include <IO/CK_string.h>
#include <stdint.h>
#include <iostream>

using namespace std;

int main(){

	uint16_t buf[] = {5, 0, 0, 1, 2, 3, 4};
	uint8_t  *p;
	CK_string str((uint8_t *)&buf);

	cout << "str size: " << str.size() << endl;
	cout << "str: ";
	for(int i = 0; i < str.size(); i++) cout << str[i] << " ";
	cout << endl;

	p = str.serialize();
	//cout << *p << endl;

	cout << "str serialize: ";
	for(int i = 0; i < 4 + 2 * str.size(); i++) cout << (int)*(p + i) << " ";
	cout << endl;

	return 0;
}
