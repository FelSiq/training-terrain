#include <iostream>

class myClass{
	//private by default
	private:
		int secretID;
	protected:
		//Getter
		int myNotSoSecretId(){return secretID;}

	public:
		myClass(){
			std::cout << "\t\tcreated directly from myClass..." << std::endl;
		}
		myClass(int param){
			std::cout << "\t\tcreated parametrized from myClass..." << std::endl;
		}

		//Other methods
		void genericFunction(){
			std::cout << "This is the myClass::genericFunction" << std::endl;
			secretID = 123456;
		}
};

class mySon: public myClass{
	public:
		int securityFail(){return myNotSoSecretId();}

		//It's redundant, becayse ": myClass()" is default.
		mySon(int z) : myClass() {
			std::cout << "created a mySon-type..." << std::endl;
		}
		mySon(int i, int j) : myClass(i + j){
			std::cout << "created a parametrized mySon-type..." << std::endl;
		}
		// will call myClass() constructor by default
		mySon(){
			std::cout << "no parameter at all..." << std::endl;
		}

		//Other methods
		void genericFunction(){
			std::cout << "This is the mySon::genericFunction" << std::endl;
		}
		
};

class otherClass {
	public:
		otherClass(){
			std::cout << "glitch?" << std::endl;
		}
};

int main(int argc, char const *argv[]){
	mySon instance(3,4);

	mySon object(4);

	//mySon object1;
	//mySon object2;

	//Will start with unparameterized constructor
	mySon memoryPlaceholder;

	//Glitched objetc -- will not call the default constructor,
	//because GCC will think this is some sort a function.
	otherClass glitchedObj();

	//This will work fine
	otherClass nonGlitchedObj;

	/*
		Experiment results:
		1. If a constructor of a derivate class does not have a 
			proper indicator of a superclass constructor, then
			the unparameterized will be called by default, if it exists at all.
		2. One can specify the constructor of superclass that has to be used
			BEFORE the specific constructor of subclass, using
			subClass(<params or not>) : superCLass(<params>){
				//What to do after superCLass(<param>) ends?
			} 
			subClass(<another params, or not if param used above>) : superClass(<another params, or might not>){
				//Same logic as above.
			}
		3. If a subclass does not have a constructor, then the superclass
			unparameterized constructor is called by default, if it exists at all.
		4. Even if a superclass unparameterized constructor is called by default,
			you can't create a instance of a subclass with a unparameterized constructor if
			the unparameterized constructor of that subclass does not exists.
		5. All characteristics of a superclass will be inheritable of its sons,
			even the private ones. However, they cannot be accessed by its sons.


		-- Extra very-important-and-unexpected information got:
		- G++ has a bug with non-parametrizes constructors
			called via myClass myInst();, because it "thinks"
			that we're calling a sort of function that returns
			a instance of myClass. However, it's not exactly like that.
			Correction: myClass myInst; (without round brackets)

	*/


	memoryPlaceholder.genericFunction();
	memoryPlaceholder.myClass::genericFunction();

	//Private stuff are still inherintable
	std::cout << memoryPlaceholder.securityFail() << std::endl;


	return 0;
}