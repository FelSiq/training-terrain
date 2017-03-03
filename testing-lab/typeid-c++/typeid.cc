#include <iostream>
#include <typeinfo>

class myClasses{};

class myDerivedClass: public myClasses{
	public:
		class MyNestedClass{};
};

using std::cout;
using std::endl; 

int main(int argc, char const *argv[]){
	myClasses *myInst = new myClasses;
	myDerivedClass *myInst2 = new myDerivedClass;
	//myDerivedClass::MyNestedClass *myInst3 = new myDerivedClass::MyNestedClass;

	myClasses *myInst4 = new myDerivedClass;

	cout << typeid(myInst).name() << endl;
	cout << typeid(*myInst).name() << endl;

	/*//Does not happen.
	if (typeid(myInst) == typeid(myInst2))
		cout << "they're equals! (1)" << endl;
	//Nor it.
	if (typeid(*myInst) == typeid(*myInst2))
		cout << "they're equals! (2)" << endl;
	//Nor it.
	if (typeid(myInst2) == typeid(myInst3))
		cout << "they're equals! (3)" << endl;*/
 
 	//Happens
 	if (typeid(myInst4) == typeid(myInst))
		cout << "they're equals! (4)" << endl;
	//Does not happens.
	if (typeid(myInst4) == typeid(myInst2))
		cout << "they're equals! (5)" << endl;

	//Neither of those below happens.
	if (typeid(*myInst4) == typeid(*myInst2))
		cout << "they're equals! (6)" << endl;
	if (typeid(*myInst4) == typeid(myInst))
		cout << "they're equals! (7)" << endl;
	if (typeid(myInst4) == typeid(*myInst2))
		cout << "they're equals! (8)" << endl;
	if (typeid(myInst4) == typeid(*myInst))
		cout << "they're equals! (9)" << endl;

	delete myInst;
	delete myInst2;
	//delete myInst3;
	delete myInst4;

	return 0;
}


/*

	Still inconclusive. Will retain this study later.

*/