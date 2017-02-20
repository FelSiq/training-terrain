/*
	Objectives: create a double-linked circular list...
	> somehow using the inheritance concept somewhere. (ok)
	> Node must be a generic template. (ok)
	> List must stay sorted. (ok)
*/

#include <cstdlib>
#include <iostream>
#include "dlcl.h"
#include <time.h>

int main(int argc, char const *argv[]){
	dlcList <double> *myList = new dlcList <double>();

	int keyList[10];

	for(int i = 0; i < 10; ++i){
		*(i + keyList) = rand() % 100;
		std::cout << "generated a new test key: " << *(i + keyList) << std::endl;
	}

	srand(time(NULL));
	for(int i = 0; i < 10; ++i)
		myList->add(*(i + keyList), (rand() % 100) * 1.037);

	myList->print();

	std::cout << std::endl;

	for(int i = myList->size() - 1; i > 0; --i)
		myList->rem(*(keyList + i));

	myList->print();

	delete myList;
	return 0;
}