#include <iostream>

void genericFunc(int &f){
	std::cout << "Adress of F content (content of \"local pointer\"): "<< &f  << std::endl;
		//<< "\nAdress of F itself (adress of local pointer): " << (int *) &f << std::endl;
}

int main(int argc, char const *argv[]){
	
	int a;
	std::cout << "Adress of A: " << &a <<std::endl;
	genericFunc(a);

	/*int *c = &a;
	float b;
	std::cout << &a<<"\n"<<&b << "\n" << &c << std::endl;*/

	/*
	---- Log:

	1. Local:
		A) With ref:
		0x7ffcf0b1b738 < 4 bytes A
		0x7ffcf0b1b73c < 4 bytes B
		0x7ffcf0b1b738 < same?? 4 bytes A

		B) With pointer:
		0x7ffcc6894b18 < 4 bytes A
		0x7ffcc6894b1c < 4 bytes B
		0x7ffcc6894b20 < 8 bytes C

	2. Calling functions
		A) with reference
			Adress of A: 0x7ffe2d57e3f4
			Adress of F content (content of "local pointer"): 0x7ffe2d57e3f4

		B) with pointers:
			Adress of A: 0x7ffd3e027194
			Adress of F content (content of local pointer): 0x7ffd3e027194
			Adress of F itself (adress of local pointer): 0x7ffd3e027158

	3. Conclusions
		It's not possible to get the adress of pointer when passing to a function
		by reference, because its automatically deferenced at run time.

		When referencing inside a function, then the reference does not
		stack. It is simply changed to its original adress by the compiler.

	*/

	return 0;
}