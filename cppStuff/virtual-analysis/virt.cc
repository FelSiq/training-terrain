#include <iostream>

class myClassA{
	public:
		virtual void print(){
			std::cout << "This is myClassA print..." << std::endl;
		}

		virtual ~myClassA(){}
};

class myClassB: public myClassA{ //8 bytes
	public:
		virtual void print(){
			std::cout << "This is myClassB print..." << std::endl;
		}

		virtual ~myClassB(){}
};

class myClassC: public myClassB{ // 8 bytes
	public:
		void print(){
			std::cout << "This is myClassC print..." << std::endl;
		}

		~myClassC(){}
};


/*class myClassY{ //1 byte

};

class myClassK{ //8 + 4*100 bytes
	int vec[100];
	public:
		void print(){
			std::cout << "This is myClassB print..." << std::endl;
		}
};

class myClassX: private myClassK, public myClassY, public myClassA{ //8 bytes

};*/


//A << B << C


class sizeNonVirtual{
	public:
		void funcA(){
			std::cout << "do nothing..." << std::endl;
		}
		void funcC(){
			std::cout << "do nothing..." << std::endl;
		}
		void funcB(){
			std::cout << "do nothing..." << std::endl;
		}
};

class sizeVirtual{
	public:
		virtual void funcA(){
			std::cout << "do nothing..." << std::endl;
		}
		virtual void funcB(){
			std::cout << "do nothing..." << std::endl;
		}
		virtual void funcC(){
			std::cout << "do nothing..." << std::endl;
		}
};

int main(int argc, char const *argv[]){
	/*
	Useful notes: 
	- a empty class have 1 byte
	- number of derivations may interfer on sons size
	- primitives types weights the expected way
	- any superclass pointer on subclass instance is legal. The reverse, however, is illegal. 

	*/

	/*std::cout << sizeof(myClassA) << "/"
		<< sizeof(myClassB) << "/"
		<< sizeof(myClassC) << "/"
		<< sizeof(myClassY) << "/"
		<< sizeof(myClassX) << std::endl;*/
	
	/*
	Test 1: direct call with virtual usage
	myClassA().print();
	myClassB().print();
	myClassC().print();

	output:
		This is myClassA print...
		This is myClassB print...
		This is myClassC print...

	*/

	/*
	Test 2: direct call without virtual usage
	myClassA().print();
	myClassB().print();
	myClassC().print();
	
	output:
		This is myClassA print...
		This is myClassB print...
		This is myClassC print...

	*/

	/*
	test 3: function call with respectives pointers, without using virtual
	myClassA instA;
	myClassB instB;
	myClassC instC;

	instA.print();
	instB.print();
	instC.print();

	output:
		This is myClassA print...
		This is myClassB print...
		This is myClassC print...

	Same result using virtual.
	*/

	/*
	Test 4: inst B and C using pointer to A, using virtual

	output:
		This is myClassA print...
		This is myClassB print...
		This is myClassC print...

	Test 5: same, but without virtual

	output:
		This is myClassA print...
		This is myClassA print...
		This is myClassA print...

	Test 6: B using pointer to A, and C using pointer to B, without virtual

	output:
		This is myClassA print...
		This is myClassA print...
		This is myClassB print...

	Test 7: same, but using virtual

	output:
		This is myClassA print...
		This is myClassB print...
		This is myClassC print...

	*/
	myClassA *instA = new myClassA;
	myClassA *instB = new myClassB;
	myClassB *instC = new myClassC;

	instA->print();
	instB->print();
	instC->print();

	delete instA;
	delete instB;
	delete instC;

	//Without variables
	std::cout << sizeof(sizeVirtual) << '/' << sizeof(sizeNonVirtual) << std::endl;
	//output: 8/1

	//With "int x"
	//output: 16:4

	return 0;
}