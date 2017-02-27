#include <iostream>
#include <cstdlib>

/*int *aFunction(int x){
	static int myVar = x;
	myVar++;
	return &myVar; 
}*/

/*int *aFunction2(){
	static int *pointer = NULL;
	return pointer;
}*/

class myClassA{
	//static int myVar; //(1)
	protected:
		//static int myVar; //(2)
		//const int myVar = 200; //Only on c++11 ao so on.
		//static const int myVar = 100; //Can only be initialized THIS way
		int myVar;
	public:

		//Works only if myVar is not static
		//myClassA() : myVar(200){}

		/*myClassA(){
			//std::cout << x++ << std::endl;
		}*/

		/*~myClassA(){
			static int k = 0;
			k++;
		}*/

		//static int getVar();
		//static int getVar(float z);
		int getVar(){return myVar;}
		//int getVar(){return myVar;}
		//WHen testing "static const", this must be desabilited
		//void setVar(int newVar){myVar = newVar;}

		/*int genericMethod(int k){
			static int x = k;
			return x;
		};*/
};

//int myClassA::myVar; //(1) (2)

//int myClassA::getVar() {return myVar;} //(2)
/*int myClassA::getVar(float z) {
	std::cout << z << std::endl;
	return myVar;
}*/
//Fun fact: C++ ALWAYS create floating points on the fly as DOUBLE!
//If a does not exists a overloaded version with double, and only with float
//the compiler will still bothers you!
/*int myClassA::getVar(double z) {
	std::cout << "double!" << std::endl;
	return myVar;
}*/

class myClassB: public myClassA{
	//int myVar;
	public:
		
		/*void setVar(int newVar){myVar = newVar;}
		int getVar() const{return myVar;}*/
};

//int myClassB::getVar() {return myVar;} //(2)

void genericFunction(int x){
	static const float f = (float) x * 1.1;
	std::cout << f << std::endl;
}

int main(int argc, char const *argv[]){
	
	/*
	Stuff used on tests 1 and 2.

	int *pointer,
	aux = atoi(*(argv + 1));
	*/

	/*
	Test 1: static variable on function
	- Behaviour almost like the same on the C language,
		whoever, static functions can be initialized with
		other variables aswell.

		int const x, static int myVar = x : ok.
		int x, static int myVar = x : ok.
		static int myVar = 5 : ok!
	
	int k = 5;
	while(0 < aux--)
		pointer = aFunction(k);
	std::cout << *pointer << std::endl;
	*/

	/*
	Test 2: static pointer on function
	- Pointers can be "new/malloc" on the initialization.
	- Seens like the static thing on C was poor worked, and corrected on C++.
	- The adress stays the same, as the static variables are still initialized only once.
		static int *pointer = new int[5] : ok
		static int *pointer = NULL : ok!

	fun note: NULL == 0, literally, on C++

	*/

	/*while(0 < aux--){
		pointer = aFunction2();
		std::cout << pointer << std::endl;
	}
	
	delete [] pointer;
	*/

	/*
	Test 3: static variable on C++ classes
	- if a class has a static member on it, then it must be
		defined somewhere else on the source file.
		This actually makes sense, as a static variable are a sort
		of global variable, but just on the class scope¹.

	- Modifying a static variable on any instance of a superclass/subclass,
	leads to ALL instances on this hierarchy to have the static member modified:

		command: (instA + 3)->setVar(17);
		InstA #0: 0	InstB #0: 0
		InstA #1: 0	InstB #1: 0
		InstA #2: 0	InstB #2: 0
		InstA #3: 0	InstB #3: 0
		InstA #4: 0	InstB #4: 0
		----------------
		InstA #0: 17	InstB #0: 17
		InstA #1: 17	InstB #1: 17
		InstA #2: 17	InstB #2: 17
		InstA #3: 17	InstB #3: 17
		InstA #4: 17	InstB #4: 17

		¹:
		adresses:
		InstA #0: 0x60224c	InstB #0: 0x60224c
		InstA #1: 0x60224c	InstB #1: 0x60224c
		InstA #2: 0x60224c	InstB #2: 0x60224c
		InstA #3: 0x60224c	InstB #3: 0x60224c
		InstA #4: 0x60224c	InstB #4: 0x60224c

	*/

	/*myClassA *instA = new myClassA[5];
	myClassB *instB = new myClassB[5];

	for(int i = 0; i < 5; ++i){
		std::cout 
			<< "InstA #" << i << ": "
			<< (instA + i)->getVar()
			<< "\tInstB #" << i << ": "
			<< (instB + i)->getVar()
			<< std::endl;
	}

	(instB + 3)->setVar(17);

	std::cout << "----------------" << std::endl;

	for(int i = 0; i < 5; ++i){
		std::cout 
			<< "InstA #" << i << ": "
			<< (instA + i)->getVar()
			<< "\tInstB #" << i << ": "
			<< (instB + i)->getVar()
			<< std::endl;
	}

	std::cout << "adresses:" << std::endl;

	for(int i = 0; i < 5; ++i){
		std::cout 
			<< "InstA #" << i << ": "
			<< ((instA + i)->getVar())
			<< "\tInstB #" << i << ": "
			<< ((instB + i)->getVar())
			<< std::endl;
	}

	delete [] instA;
	delete [] instB;*/

	/*
	Test 4: static methods on classes on C++
	- Interesting, static methods can't have cv-qualifiers (neither special *this* pointer):
		static member function ‘static int myClassA::getVar()’ cannot have cv-qualifier
		   static int getVar() const{return myVar;}
	- Static methods can't access private members of a class
		static.cc:25:5: error: ‘int myClassA::myVar’ is private
		 int myClassA::myVar; //(1) (2)

	- Static methods can only access STATIC members of a class 
		static.cc: In static member function ‘static int myClassA::getVar()’:
		static.cc:27:32: error: invalid use of member ‘myClassA::myVar’ in static member function
		 int myClassA::getVar() {return myVar;}
		                                ^
		static.cc:18:7: note: declared here
		   int myVar;

	- Static methods can be acessed without any class instance, just like a normal function.
		std::cout << myClassA::getVar() << std::endl;

	- Static methods and members (variavles) can be overhidden on subclasses with no problem.
		The subclass can then call any form of the method.

	- Static methods can be overloaded with no problem.
		std::cout << myClassA::getVar() << std::endl;
		std::cout << myClassA::getVar(0.576) << std::endl;

	- The overload and the overhidden can be between static and non-static versions aswell.

		Test:
			myClassB *instB = new myClassB;
	
			instB->myClassA::setVar(5);
			instB->setVar(17);

			std::cout << instB->getVar() << std::endl;
			std::cout << myClassA::getVar() << std::endl;

	- Standard:
	    2) [ Note: A static member function does not have a this pointer (9.3.2). —end note ] 
	    A static member function shall not be virtual. There shall not be a static and a non-static member 
	    function with the same name and the same parameter types (13.1).

	    A static member function shall not be declared const, volatile, or const volatile.

	*/

	/*
	Test 5: static variable inside methods on classes on C++
	- They are global variable but only on the class scope:
		InstA #0: 0x6021b4	InstB #0: 0x6021b4
		InstA #1: 0x6021b4	InstB #1: 0x6021b4
		InstA #2: 0x6021b4	InstB #2: 0x6021b4
		InstA #3: 0x6021b4	InstB #3: 0x6021b4
		InstA #4: 0x6021b4	InstB #4: 0x6021b4
	- Adress does not change even on future instances.
	- They will be initialized only on the very first call of the function,
		and then never anymore. 

	- Fun-fact: constructors can have static variables inside it, although impossible to
		recover its adress, it may be used to do stuff depending on the static variable value.
		example: keep track of how many instances of this class was created so far.

		myClassA(){
			static int x = 0;
			std::cout << x++ << std::endl;
		}

		Destructors works the same way.

	- Extra footage: the compiler on std::cout << does not necessarily evaluates the 
		calls the same order we put it. The only fixed thing is that the output will
		obey our imposed order. 
	*/

	/*
	Expriment was made like this:

	myClassA *instA = new myClassA[5];
	myClassB *instB = new myClassB[5];


	//This will be the first (and last) inicialization of the
	//x variable on ALL instance of ALL superclasses/subclasses.
	(instB + 4)->genericMethod(17);
	int k = 0;

	//No effect, other than print "17" on all values
	for(int i = 0; i < 5; ++k, ++i){
		std::cout 
			<< "InstA #" << i << ": "
			<< (instA + i)->genericMethod(k)
			<< "\tInstB #" << i << ": "
			<< (instB + i)->genericMethod(k)
			<< std::endl;
	}

	myClassB *newInst = new myClassB;

	//Still 17.
	std::cout << newInst->genericMethod(99) << std::endl; 
	//Even on future instances, the variable is still in the same adress.

	delete [] instA;
	delete [] instB;
	*/

	/*
	Test 6: const variables inside C++ class
	- Non static:
		- Must be either initialized on object constructor declaration:
			myClassA() : myVar(200){} //constructor
		or hardcoded inside the class code (only on c++11 and so on):
			const int myVar = 200; //Only on c++11 ao so on.

		static.cc:20:21: warning: non-static data member initializers only available with -std=c++11 or -std=gnu++11
		   const int myVar = 100; //Only on c++11 ao so on.
	- Static:
		- Can only be initialized on class code definition.
			static const int myVar = 100; //Can only be initialized THIS way
	*/

	/*
	Test 7: const + static inside C++ method/function

	- Nothing new: static variables are still initialized once. 
		The only difference is that this time its a constant. 
	*/

	return 0;
}