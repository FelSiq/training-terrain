#include <iostream>

class myClassA{
	public:
		virtual void genericMethod() const{
			std::cout << "This is myClassA method..." << std::endl;
		}

		virtual ~myClassA(){}
};

class myClassB: public myClassA{
	public:
		void genericMethod() const{
			std::cout << "This is myClassB method..." << std::endl;
		}
};

int main(int argc, char const *argv[]){
	/*myClassB *instB = new myClassB;

	instB->genericMethod(); //B
	instB->myClassA::genericMethod(); //A

	delete instB;*/

	myClassA *instB = new myClassB; //Inst class B <- class A

	instB->genericMethod(); //A
	//instB->instB::genericMethod(); //N pode!! (ponteiro class A)
	//myClassB *instBCopy = instB; //N pode!! (supõe-se que instB é da classe A)

	//Solução: declarar genericMethod() como virtual.

	delete instB;

	return 0;
} 