#include <iostream>

class pureVirtual{
	public:
		//Does not need the name of the parameters, just the type.
		virtual void genericMethod(int, float)=0;
		//Cannot be virtual
		//Still be called on subclasses creation.

		pureVirtual(){
			std::cout << "Created a instance of subclass of purevirtual superclass." << std::endl;
		};

		//Must be virtual, because using delete on non-virtual classes with
		//virtual functions may cause undefined behavior.
			//purevirtual.cc:37:9: warning: deleting object of polymorphic class type ‘classB’ 
			//which has non-virtual destructor might cause undefined behaviour [-Wdelete-non-virtual-dtor]
			  //delete instB;

		virtual ~pureVirtual(){};
		
		void anotherMethod(){
			//Do nothing.
		}
};

class classA: public pureVirtual{
	//Still a abstract class.
	virtual void someMethod(){
		//Do nothing 3;
	}
};

class classB: public classA{
	//Implements the pure virtual method of the  pureVirtual class.
	//Now classB is not a abstract class and can be instantiated.
	void genericMethod(int k, float z){
		//Do nothing..
	};

};

int main(int argc, char const *argv[]){
	//classA instA; //Can not do that.
	classB *instB = new classB;

	delete instB;
	return 0;
}