#include <iostream>
#include <fstream>
#include <cstdio>

enum{
	PROGNAME,
	PARAM,
	NUMARGS
};

int main(int argc, char const *argv[]){
	if (argc == NUMARGS){
		std::fstream *fp = new std::fstream("test.out", 
			std::fstream::in | std::fstream::binary);

		char c;
		while(fp->get(c))
			std::cout << (int) (unsigned char) c << std::endl;
		
		delete fp;
		return 0;
	}
	std::cout << "usage:" << *(argv + PROGNAME) << " <arg num>" << std::endl;
	return 1;
}