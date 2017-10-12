#include <iostream>
#include "namescape.h"

namespace myMain{
	class myClass{
		public:
			void genericFunc(){
				cout << "This is generic function from MAIN!" << endl; 
			}
	};
};

int main(int argc, char const *argv[]){
	myLib::myClass myInst;
	myMain::myClass myInst2;

	myInst.genericFunc();
	myInst2.genericFunc();

	/*
	output:

	This is generic function from my lib!
	This is generic function from MAIN!

	*/

	//This can't happen
	//myLib::myClass *myPointer = new myMain::myClass;
	//delete myPointer;

	return 0;
}