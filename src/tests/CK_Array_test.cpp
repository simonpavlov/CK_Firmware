#include <IO/CK_Array.h>
#include <iostream>
#include <cstdlib>

using namespace std;

int main(){
	Array *arr1 = new Array(10);
	Array arr3;

	for(int i = 0; i < arr1->size(); (*arr1)[i] = i++);

	arr3 = *arr1;
	Array arr2(*arr1);

	if(arr2.app_end(*arr1)) cout << "OK" << endl;

	cout << "arr1: " << *arr1 << endl;

	delete arr1;

	arr1 = new Array(3);

	// arr1 = new Array(100);
	// char *pointer = (char *)malloc(10000);

	arr3.take_front(arr1->data(), 3);

	cout << "arr1: " << *arr1 << endl
		<< "arr2: " << arr2 << endl
		<< "arr3: " << arr3 << endl;

	cout << "FINISH!" << endl;

	delete arr1;

	return 0;
}