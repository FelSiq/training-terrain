#include <iostream>

class myClassA{
	private:
		int x;
	public:
		virtual void print(){
			std::cout << "This is myClassA print..." <<std::endl;
		}
		virtual ~myClassA(){};
};


class myClassB : public myClassA{
	private:
		double y;
	public:
		void print(){ 	//"Rewrite" - not literally, but this means that this
						// method "signature" (considering only the arguments) is exactly the 
						//same of the superclass correspondent method. This is 
						//not a overload, because the signature does not change.
			std::cout << "This is myClassB print..." <<std::endl;
		}
		void genericFunc(){
			//Do nothing...
		}
};


int main(int argc, char const *argv[]){
	myClassB *instB = new myClassB;

	myClassA *pointerA = instB;

	/*
	Do not work
	output: 
	inheritPointer.cc:32:12: error: ‘class myClassA’ has no member named ‘genericFunc’
	  pointerA->genericFunc();

	pointerA->genericFunc();
	*/

	delete pointerA;

	return 0;
}