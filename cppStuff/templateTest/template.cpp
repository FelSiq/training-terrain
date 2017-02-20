#include <iostream>

template <class T>
class myClass{
	private:
		T myVar;
	public:
		void TestMethod(){
			std::cout << "TestMethod.\n";
		}
		void changeVar(T newVal){
			std::cout << "Changing var...\n";
			myVar = newVal;
		}
		T retVar(){
			return myVar;
		}
};

int main(int argc, char const *argv[]){
	myClass<double> *instance = new myClass<double>();

	instance->changeVar(23);

	std::cout << std::to_string(instance->myVar) + '\n';

	std::cout << std::to_string(instance->retVar()) + '\n'	;

	delete instance;
	return 0;
}