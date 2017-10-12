#include <iostream>
#include <cstdlib>

int main(int argc, char const *argv[]){
	char *myChar = new char[0];

	std::cout << myChar << std::endl; //Does not print anything.

	//free(myChar); (2)
	//myChar = NULL; //(1)
	delete [] myChar; //If (1) is deleted and (2) not, a double-free error will occur
	
	char *myPointer = NULL;
	delete myPointer; 	//Even if myPointer is NULL, this 
						//does not cause any error/segmentation fault.

	/*
	Talking of heap allocation...

	Extra footage:
		(char *myChar = new char)  != (char *myChar = new char[1])
		The first should be deleted without [], because it is a single unit.
		The second should be deleted with [], because its an array holding a single unit. 
	*/
	
	return 0;
}