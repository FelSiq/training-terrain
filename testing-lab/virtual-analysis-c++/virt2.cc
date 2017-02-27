#include <iostream>

class myClassA{
	public:
		virtual void print(){
			std::cout << "This is myClassA print..." << std::endl;
		}

		virtual ~myClassA(){};
};

class myClassB: public myClassA{ //8 bytes
	public:
		void print(){
			std::cout << "This is myClassB print..." << std::endl;
		}

		~myClassB(){}
};

class myClassC: public myClassB{ // 8 bytes
	public:
		void print(){
			std::cout << "This is myClassC print..." << std::endl;
		}

		~myClassC(){}
};

int main(int argc, char const *argv[]){
	
	myClassA *instA = new myClassA;
	myClassA *instB = new myClassB;
	myClassB *instC = new myClassC;

	instA->print();
	instB->print();
	instC->print();

	/*
	TEST 1: no print on A, and no virtual on B. C has a B's pointer.
	output:
		This is myClassB print...
		This is myClassB print...

	TEST 2: pure virtual on A, no virtual on B.
		note: can't create instance of A.
	output:
		This is myClassB print...
		This is myClassC print...

	TEST 3: same, but virtual on B.
	output:
		This is myClassB print...
		This is myClassC print...

	TEST 4: B uses A pointer, C uses B pointer. Virtual only on A.
	output:
		This is myClassA print...
		This is myClassB print...
		This is myClassC print...

	Virtual behavior of a superclass seens to implicitly descend on the subclasses.
	However, programming-wise, explicitly redeclaring the virtual behavior of a method
	seens to be reasonably clearer.

	*/

	delete instA;
	delete instB;
	delete instC;

	return 0;
}