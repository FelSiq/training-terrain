#include <iostream>
#include "asciivec.h"

int main(int argc, char const *argv[]){
	//string *n = new string("2834"), *m = new string("234.432");
	string n("9182"), m("9283.4234");

	int i = n;
	double k = m;

	std::cout << i - 1 << std::endl;
	std::cout << k + 1.0 << std::endl;

	asciivec mtVec = n;

	asciivec res = mtVec + 1;

	string newStr = res;

	mtVec.print();
	res.print();
	std::cout << newStr.get() << std::endl;

	string originalStr = res - 1;
	originalStr.print();

	asciivec originalMT = originalStr;

	originalMT.print();

	return 0;
}