#include <iostream>

class myClassA{
	public:
		void genericFunc(){
			std::cout << "this is class A function..." << std::endl;
		}

		//Constructor
		myClassA(){
			std::cout << "Created a class A instance..." << std::endl;
		}

		myClassA(int k){
			std::cout << "Created a parameterized class A instance..." << std::endl;
		}
};

class myClassB{
	public:
		void genericFunc(){
			std::cout << "this is class B function..." << std::endl;
		}
		myClassB(){
			std::cout << "Created a class B instance..." << std::endl;
		}
		myClassB(int z){
			std::cout << "Created a parameterized class B instance..." << std::endl;
		}
};

class myClassC: public myClassB, public myClassA{
	public:
		myClassC() : myClassA(0){
			std::cout << "Created a class C instance..." << std::endl;
		}
};


int main(int argc, char const *argv[]){
	
	/*Multi-enhiridit tests:

	test 1: C are derivative of A and B, but B is already a derivative of A
	output: multenhiridit.cc:9:7: warning: direct base ‘myClassA’ inaccessible in ‘myClassC’ due to ambiguity
	 class myClassC: public myClassA, protected myClassB{

	test 2: keep test 1, try to change the keyword in C to private/protected in relation of A
	output: both same as above.

	test 3: create a polymorphic function on class A and B, and try to call on C.
	output: multenhiridit.cc:36:9: error: request for member ‘genericFunc’ is ambiguous
	  myInst.genericFunc();
	  solution: use scope operator :: and specify a call.

	test 4: constructors. Both class A and B has a default constructor to C (non-parameterized).
	Result: both constructors are called. The order on class C declaration,
		class myClassC: public myClassB, public myClassA{

		};,
	MATTERS, as constructor of B will be called before constructor A.
	output: Created a class B instance...
			Created a class A instance...
	
	test 5: class C has a non-parameterized constructor, but unspecified superclass constructor.
	result: corroborates the test above.
	output:
		Created a class B instance...
		Created a class A instance...
		Created a class C instance...

	test 6: try to call superclass A constructor before class B constructor
	result: negative. can't force that.
	output:
		multenhiridit.cc: In constructor ‘myClassC::myClassC()’:
		multenhiridit.cc:34:37: warning: base ‘myClassA’ will be initialized after [-Wreorder]
		   myClassC() : myClassA(), myClassB(){
		                                     ^
		multenhiridit.cc:34:37: warning:   base ‘myClassB’ [-Wreorder]
		multenhiridit.cc:34:3: warning:   when initialized here [-Wreorder]
		   myClassC() : myClassA(), myClassB(){

	test 7: overload class A and B constructors, but does not specify on class C constructor
	result: as already seen on simple inherit, all superclasses default unparameterized construtor are called.

	test 8: overload class A and B constructors, and does specify on class C constructor
	result: everything as expected. Note: the specification needs to follow the
		order on class C declaration. Use comma to separate the values, i.e:
			myClassC() : myClassB(-9), myClassA(0){
				std::cout << "Created a class C instance..." << std::endl;
			}
		note 2: you don't need to specify all superclasses constructors. In these classes,
			the default unparameterized constructor will be called.

	test 9: does not create unparameterized constructors on any superclass, but keep another constructor
	result: error, because default constructor are not found
	output:
		multenhiridit.cc: In constructor ‘myClassC::myClassC()’:
		multenhiridit.cc:34:13: error: no matching function for call to ‘myClassB::myClassB()’
		   myClassC(){

		multenhiridit.cc:19:7: note:   candidate expects 1 argument, 0 provided
		multenhiridit.cc:34:13: error: no matching function for call to ‘myClassA::myClassA()’
		   myClassC(){

	test 10: does not create any constructor on superclasses at all.
	result: works fine.

	*/

	myClassC myInst;

	return 0;
}