#include <IO/CK_String.h>
#include <stdint.h>
#include <iostream>

using namespace std;

int main(){

	uint16_t buf[] = {5, 0, 0, 1, 2, 3, 4};
	uint8_t  *p;

	CK_String str((uint8_t *)buf);

	str[1] = 1024;

	cout << "str size: " << str.size() << endl;
	cout << "str: ";
	for(int i = 0; i < str.size(); i++) cout << str[i] << " ";
	cout << endl;

	p = str.serialize();
	//cout << *p << endl;

	cout << "str serialize: ";
	for(int i = 0; i < 4 + 2 * str.size(); i++) cout << (int)*(p + i) << " ";
	cout << endl;

	uint8_t buf2[] = {0xFF, 0xFF, 0xFF, 0xFF};
	CK_String str1((uint8_t *)buf2);

	if(str1.size()){
		cout << "str1 NOT empty!" << endl;
	}
	else{
		cout << "str1 empty!" << endl;
	}

	return 0;
}
