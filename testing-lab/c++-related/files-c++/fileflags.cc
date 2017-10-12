#include <iostream>
#include <fstream>

int main(int argc, char const *argv[]){
	//There's the status flags too.
	//Like the file open status, those flags
	//are stored in bits of a byte too.

	/*
	std::cout << std::fstream::goodbit << std::endl; 	//000 (0)
	std::cout << std::fstream::badbit << std::endl; 	//001 (1)
	std::cout << std::fstream::eofbit << std::endl; 	//010 (2)
	std::cout << std::fstream::failbit << std::endl; 	//100 (4)
	*/

	/*
	
	

	*/

	//Test 0
	std::ifstream *myInput = new std::ifstream("test");
	//std::ofstream *myOutput = new std::ofstream("test");

	std::cout << "Flags test #0 and #3" << std::endl;
	std::cout << "Input flags: " << myInput->rdstate() << std::endl;

	//Test 3:
	std::cout << "goodbit (0):\t" << myInput->good() << std::endl;
	std::cout << "badbit (1):\t" << myInput->bad() << std::endl;
	std::cout << "eofbit (2):\t" << myInput->eof() << std::endl;
	std::cout << "failbit (4):\t" << myInput->fail() << std::endl;
	/*
	test 3 output on the very first opening:
		goodbit (0):	0
		badbit (1):		0
		eofbit (2):		0
		failbit (4):	1 (file not found)
	then on all other openings:
		goodbit (0):	1 (no error ocurred this time)
		badbit (1):		0
		eofbit (2):		0
		failbit (4):	0

	*/
	
	//std::cout << "Output flags: " << myOutput->rdstate() << std::endl;


	/*
	Output on the very first execution:
		Input flags: 4 (0100) - "fail flag"
		Output flags: 0 (0000)

	Output on second execution and so on:
		Input flags: 0 (0000)
		Output flags: 0 (0000)
	*/

	//We can use the clear() method to set up desired flags.
	//By default, the byte are set to 0, i.e all bit flags 
	//are cleared.

	/*
	//Test 1
	myInput->clear(std::fstream::eofbit | std::fstream::failbit);
	myOutput->clear((std::fstream::iostate) 8.5); //Invalid state works ok

	std::cout << "Flags test #1" << std::endl;
	std::cout << "Input flags: " << myInput->rdstate() << std::endl; //output: 6
	std::cout << "Output flags: " << myOutput->rdstate() << std::endl; //output: 8
	*/
	
	/*
	Test 2
	myInput->clear();
	myOutput->clear();

	std::cout << "Flags test #2" << std::endl;
	std::cout << "Input flags: " << myInput->rdstate() << std::endl; //output: 0
	std::cout << "Output flags: " << myOutput->rdstate() << std::endl; //output: 0
	*/

	/*
	//Works as intendeed to be.
	if (myInput->good())
		std::cout << "Nothing wrong with myInput! (" << myInput->good() <<")" << std::endl;
	*/

	delete myInput;
	//delete myOutput;

	return 0;
}