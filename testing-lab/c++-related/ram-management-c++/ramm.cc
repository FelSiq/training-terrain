#include <iostream>
#include <sstream> //RAM management with strings C++
/*
	- endl : '\n' + synch
	- ends : '\0'

	//char myString[] = "felipe";
	//std::cout << myString << std::ends << std::endl;
*/

int main(int argc, char const *argv[]){

	//A string stream is openned in both input and output mode
	//One can specify the flags using std::stringstream::in and "::"::out.
	//std::stringstream *myStream = new std::stringstream;

	//Input only
	//std::stringstream *myStream = new std::stringstream(std::stringstream::in);
	//Output only
	//std::stringstream *myStream = new std::stringstream(std::stringstream::out);

	//char mystring[] = "felipe!";
	//std::stringstream *myStream = new std::stringstream(mystring);

	std::stringstream *myStream = new std::stringstream;

	int aux0, aux1;
	//Pretty much like scanf
	std::cin >> aux0; 
	std::cin >> aux1;

	//Put the information on a strstream
	*myStream << aux0*2 << ' ' << aux1 * 2 << std::endl;

	//Use mystrstream.str() to get the string inside it.
	std::cout << myStream->str() << std::endl;

	/*
	stringstream does have the stream flags aswell.
	std::cout << myStream->good() << std::endl;
	std::cout << myStream->bad() << std::endl;
	std::cout << myStream->fail() << std::endl;
	std::cout << myStream->eof() << std::endl;

	*/

	delete myStream;
	return 0;
}