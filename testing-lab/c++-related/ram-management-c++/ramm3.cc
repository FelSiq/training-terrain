#include <iostream>
#include <sstream>

using std::stringstream;
using std::endl;
using std::ends;
using std::cout;

int main(int argc, char const *argv[]){
	stringstream *myIOSstream = new stringstream;

	*myIOSstream << "Knowledge make you crazy: this is the";

	//Pointers on stringstream are actually separated.
	
	//cout << myIOSstream->stringstream::tellg() << endl; //0
	//cout << myIOSstream->stringstream::tellp() << endl; //17

	char mybuffer[80];
	myIOSstream->getline(mybuffer, 80, ' ');

	cout << mybuffer;

	/*
	cout << stringstream::beg << endl; //0 
	cout << stringstream::cur << endl; //1
	cout << stringstream::end << endl; //2

	absolute values can be used only if they are cast into 
	(std::ios::seekdir) or (stringstream::seekdir).

	*/

	myIOSstream->seekg(14, (std::ios::seekdir) 1);

	*myIOSstream << " truth." << ends << endl;

	/*
	cout << myIOSstream->tellg() << endl;//24
	cout << myIOSstream->tellp() << endl;//46
	*/

	myIOSstream->getline(mybuffer, 80, '\n');
	cout << mybuffer << endl;
	//output: Knowledge: this is the truth.

	/*
	cout << myIOSstream->tellg() << endl;//46
	cout << myIOSstream->tellp() << endl;//46
	*/

	delete myIOSstream;

	return 0;
}