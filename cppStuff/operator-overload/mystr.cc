#include <iostream>
#include "string.h"

//Operators overload on strings.
//May have leaks.
int main(int argc, char const *argv[]){
	string *myStr = new string("Uhuul.");

	std::cout << myStr->get() << std::endl;


	*myStr = "New!";

	std::cout << myStr->get() << std::endl;

	string *anotherStr = *myStr + " and Ahaaaa."; 


	std::cout << anotherStr->get() << std::endl;

	*myStr += anotherStr;

	std::cout << myStr->get() << std::endl;

	*anotherStr = "Descon.";
	
	*myStr = anotherStr;

	*anotherStr += " and something more...";

	std::cout << myStr->get() << std::endl;
	std::cout << anotherStr->get() << std::endl;

	delete anotherStr;
	delete myStr;

	return 0;
};