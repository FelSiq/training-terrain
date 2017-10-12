#include <iostream>

class myClassA{//Abstract superclass
	public:
		virtual void print() = 0; //Pure virtual
		virtual ~myClassA(){};
};

class myClassB: public myClassA{ 
	//Still abstract, as it does not redef. myClassA::print()
};

class myClassC: public myClassB{ //Not abstract anymore, can generate instances
	public:
		void print(){
			std::cout << "This is myClassC print..." << std::endl;
		}

		~myClassC(){}
};

int main(int argc, char const *argv[]){
	myClassA *instC = new myClassC;

	instC->print();

	/*
	Abstract classes: classes that do not generate any instances.
	Its purpose is to serve as a template do its derivatives classes.

	A virtual pure method is a virtual method that lacks definition, only has 
	a declaration.

	Any classe with a pure virtual function is automatically a abstract class.

	Any derivative class that do not redefine its superclasses pure virtual function 
	is a abstract class too.

	An abstract class does not necessarily dispense destructor, as it may still be 
	used to descend its "virtuality" to its derivatives destructors.

	A destructor can not be pure virtual, even on an abstract class, as pure virtual methods
	expects redefinition of itself on a derivative subclass, alogside does not make sense a 
	redef of a destructor of a superclass on a subclass.

	*/

	delete instC;

	return 0;
}