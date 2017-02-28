#include <ios>
#include <iostream>
#include <fstream>

static char *renew(char *pointer, size_t newSize){
	char *aux = new char[newSize];
	if (pointer){
		for(size_t i = 0; i < newSize; ++i)
			*(aux + i) = *(pointer + i);
		delete [] pointer;
	}
	return aux;
};

char *readline(std::istream &myFile){
	char *buffer = NULL, c = 0;
	size_t size = 0, index = 0;
	while (c != 10){
		if (size == index){
			size = (1 + 2 * size);
			buffer = renew(buffer, size + 1);
		}
		myFile.get(c);
		*(buffer + index++) = c;
	}

	if (index > 1){
		buffer = renew(buffer, index);
		*(buffer + index - 1) = '\0';
	} else {
		delete [] buffer;
		buffer = NULL;
	}
	return buffer;
};

int main(int argc, char const *argv[]){
	
	//writing on file, class "ofstream".
	//If the second param is not defined (opening mode, just like the C fopen), 
	//then the default is ios::in for ifstream e ios::out for ofstream.
	//Operators can be combined with binary OR | operator.
	std::ofstream *fout = new std::ofstream("test.out", std::fstream::out);
	//Even of that situation, the ios::out is redundant here, as a object of the
	//class std::ofstream, that flag is automatically assumed.
	if (fout->is_open()){
		std::cout << "creating a new test.out file..." << std::endl;
		*fout << "This is a" << std::endl;
		*fout << "test :)." << std::endl;
		fout->close();
	}

	//The adress is maintained after file closes.
	std::cout << "adress after closing: " << fout << "\t\"is_open\"? " << fout->is_open() << std::endl;

	//You can do that with no harm, however, your new input will just be ignored.
	*fout << "should go wrong!" << std::endl;

	//Note:
	//Creating a fstream object is the same of a stream with flags (out | in), or w+

	/*
		Another opening modes:
			ios::ate -> a+ (append with read and write)
			ios::app -> a (append write only)
			ios::trunc -> open and erase all file
			ios::binary -> b mode (binary)
	*/

	
	/*

	TEST 1:

	//Reading from a file, class "ifstream"
	std::ifstream fin("test.out");

	//Adress of the file.
	std::cout << fin << std::endl; //0xsomething

	
	char *myBuffer = new char[80];
	while(fin.getline(myBuffer, 80, '\n')){ //Third argument as '\n' just for the sake of completeness.
		//This is not good, as it interpret spaces as a terminator by default.
		//fin >> myBuffer;
		//A better option: input.getline(char * BUFFER, size_t MAXSIZE, char TERMINADOR = '\n')
		//As you see, if the terminator (third argument) is not specified, '\n' is taken by default. 
		std::cout << myBuffer << std::endl; //As expected, the terminator character (by default '\n')
											//Are not taken into the buffer, thus the 'extra' std::endl.
	
	//When file ends, the adress if automatically lost.
	std::cout << myBuffer << std::endl; //0

	elete [] myBuffer; //[] are mandatory, or else undefined behaviour.
	}
	*/

	//TEST 2
	char *myBuffer = readline(std::cin);
	//char * are printed as string
	//std::cout << myBuffer << std::endl;

	//note: "ate: The output position starts at the end of the file."
	//If flag "ate" is set, but "out" is not, it will FAIL. "app" works without "out".
	std::fstream *myOut = new std::fstream("test.out", std::fstream::in | 
		std::fstream::out | std::fstream::ate);

	*myOut << myBuffer << std::endl;

	//C++ NON-FILE streams (like string/RAM streams) have different "pointers" of position
	//of both write and read next position. So, we must use different methods
	//to get or set the current position or write and read.

	//ftell() -> tellg() (get/read) and tellp(put/write)
	//	return is not a size_t, and yes a streampos type.

	//fseek: -> seekg and seekp, howverr this function is overloaded:
	//	seekg(pos)/seekp(pos): set the absolute pos value on the respective pointer
	//	seekg(pos, whence)/seekp(pos, whence): just like the offset, you can set 
	//		relative positions using the whence parameter:
	//		-> std::stream::beg
	//		-> std::stream::end
	//		-> std::stream::cur

	//For FILE STREAMS, both pointers are interchangeable by standard:
	//"A joint file position is maintained for both the input sequence and the output sequence."

	std::streampos k = 10;

	myOut->seekp(k, std::fstream::beg); //Does not matter if "seekp" or "seekg",
										//because it's a file stream.
	std::cout << myOut->tellg() << std::endl; //10
	std::cout << myOut->tellp() << std::endl; //10
	//neiter tells matter now.


	myOut->getline(myBuffer, 80, '\n');
	std::cout << myBuffer << std::endl;//outs: "test :)."

	delete [] myBuffer;

	/*
	Concept of file synchronization:
	- All data being writen in a opened file, is not writen directly on the file.
	All objects of fstream class are derived of the superclass streambuf (you can check
	this fact on the libraries dependencies), which acts as a "intermediary buffer".
	The OS can impose another intermediaries buffers aswell.

	The real insertion the file happens on the process called synchronization. In C++,
	this happens under certain conditions: 
	
	- You can force sync using the method sync() on all fstream classes. 
		Return 0 if succesfull, -1 otherwise.
	- Or you can force with the manipulators endl or flush.
	- Or when a file is closed, either by the programmer or automatically on the object destruction.
	- Or forced automatically, when the intermediary buffer is full. 
	*/

	//C++ files are closed auto uppon object destructors.
	myOut->close();
	delete myOut;


	return 0;
}