#include <iostream>

class myClass{
	public:
		void printThis(){
			std::cout << this << std::endl;
		}

};

int main(int argc, char const *argv[]){

	myClass *a = new myClass;

	a->printThis();
	std::cout << a << std::endl;

	return 0;
}