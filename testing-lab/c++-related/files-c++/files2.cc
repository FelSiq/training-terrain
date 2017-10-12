#include <iostream>
#include <fstream>
#include <string>

class myRegister{
	private:
		//Only thpse three parameters matters for the write-and-read of this
		//class, the methods does not.

		//This causes segfault.
		//std::string name;
		char age;
		unsigned int id;
	public:
		myRegister(/*std::string newName = "unknown",*/ char const newAge = 0,
			int const newId = -1){
			
			//name = newName;

			age = newAge;
			id = newId;
		}

		void print(){
			std::cout << "PERSON REGISTER:" << std::endl
				//<< "\tNAME: " << this->name << std::endl
				<< "\tAGE: " << (short int) this->age << std::endl
				<< "\tID: " << this->id << std::endl << std::endl; 
		}

		//No need of getters to dump the data.
};

enum{
	PROGNAME,
	NUMREGIS,
	ARGNUM
};

int main(int argc, char const *argv[]){
	if (argc != ARGNUM){
		std::cout << "usage: " << *(PROGNAME + argv) 
			<< " <# of registers>" << std::endl;
		exit(1);
	}

	if (atoi(*(argv + NUMREGIS)) > 0){
		int regixNum = atoi(*(argv + NUMREGIS));
		//write() and read() are the appropriated functions,
		//for output and input, respctively, of object data.

		myRegister *person = NULL;
		//Create output file
		//App = append in write-only mode (do not need out mode like "ate")
		std::ofstream *fout = new std::ofstream("regix", 
			std::fstream::app);

		//My keyboard buffers.
		std::string buffer[3];

		do {
			std::cout << "please insert a valid <name>" <<
				"<age> <id> for a new register: " << std::endl;
			getline(std::cin, *buffer);
			getline(std::cin, *(1 + buffer));
			getline(std::cin, *(2 + buffer));

			//Warning: std::stoi are only on c++11 and foward
			person = new myRegister(/**buffer,*/ std::stoi(*(buffer + 1), NULL), 
				std::stoi(*(buffer + 2), NULL));

			//endl = end-of-line + explicity synchronization

			//The object pointer must be a char *
			fout->write((char *) person, sizeof(person));

			delete person;
			person = NULL;
		} while (--regixNum > 0);

		//Do not need close the file manually.
		fout->close(); //But just for the sake of completeness.
		delete fout;
	} else {
		//Read from the regix file
		std::ifstream *fin = new std::ifstream("regix");
		myRegister dummy;
		if (fin && fin->is_open()){
			std::cout << "lets start...!" << std::endl;
			while(fin->read((char *) &dummy, sizeof(myRegister))){
				std::cout << "got one!" << std::endl;
				dummy.print();
			}
			fin->close();
		}
		delete fin;
	}
	return 0;
}