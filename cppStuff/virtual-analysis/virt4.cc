#include <iostream>

class myClassA{
	protected:
		int x;
	public:
		myClassA(){
			std::cout << "Created a class A instance..." << std::endl;
		}

		virtual ~myClassA(){}
};

class myClassB: virtual public myClassA{ 
	public:
		myClassB(){
			std::cout << "Created a class B instance..." << std::endl;
		}
};

class myClassC: virtual public myClassA{
	public:
		myClassC(){
			std::cout << "Created a class C instance..." << std::endl;
		}
};

class myClassD: public myClassB, virtual public myClassC{ 
	//C's constructor will be called first, because its virtual, 
	//and its methods are elegible to "redefinition".
	public:
		int getX(){return x;}
		myClassD(){
			std::cout << "Created a class D instance..." << std::endl;
		}
};

int main(int argc, char const *argv[]){
	myClassA *instD = new myClassD;

	/*
	TEST 1: declare x on A, get x on D, neither B and C are virtual derivatives of A

	output:
	virt4.cc:18:21: error: reference to ‘x’ is ambiguous
	   int getX(){return x;}

	This error persist even if:
		- Class D are virtual derivative of or B, or C, or both.
		- if or class B or class C are virtual derivative of A.

	*/

	/*
	TEST 2: same, but B and C both are virtual derivative subclasses of superclass A
	
	result: works fine.

	This happens because, in theory (not assuming any possible compiler otimizations),
	when D are declared derivative of both B and C, the B virtual "copy" of 
	superclass A are redefined to the exactly same stuff by	the virtual "copy" 
	of C. 

	The "int x", on class D are, in fact, the redefinition inside C, not B,
	due to D class declaration.

	In pratic, it does not effect the program, but avoids ambiguity.  

	*/


	delete instD;

	/*
	Commonly, the DESTRUCTOR of a subclass is called before the destructor
	of the superclass, i.e, they act in reverse order in relation of
	constructors, which makes total sense.

	However, in order to use a superclass pointer on a derivative class,
	this superclass NEEDS TO HAVE A VIRTUAL DESTRUCTOR, or else:

	*** Error in `./virt': free(): invalid pointer: 0x0000000001047c28 ***

	on delete call on the instance with superclass pointer.

	This happens exactly because, if we do not warn how things works,
	the delete function will now destruct the object correctly,
	pretty much like the call on polymorphic functions with a superclass pointer.

	The constructor, however, can't be virtual, as you obligatory creates a
	superclass instance to compose a subclass instance, when creating it. 
	Then, all constructors, when they exists, must be called.

	The "default unparameterized superclass constructor call" keeps the same,
	regardless of all that stuff.

	*/

	return 0;
}