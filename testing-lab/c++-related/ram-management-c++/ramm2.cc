#include <iostream>

class string{
	private:
		//members
		char *__str;
		unsigned long int __size;
		/*
		- keyword "explicit" can only be used within constructors and conversion operators 
			ramm2.cc:10:35: error: only declarations of constructors and conversion operators can be ‘explicit’
			    unsigned long int &__newStrSize){
		*/

		void copyString(char const newStr[], 
			unsigned long int &__newStrSize){
			this->__str = new char[__newStrSize + 1];
			this->__size = __newStrSize;
			while(0 < __newStrSize--)
				*(__newStrSize + this->__str) = *(__newStrSize + newStr);
			*(this->__str + __newStrSize) = '\0';
		}

	public:
		//Overloaded constructors
		string(){
			this->__str = NULL;
			this->__size = 0;
		}

		explicit string(char const newStr[]){
			unsigned long int __newStrSize = 0;
			for (__newStrSize = 0; 
				*(newStr + __newStrSize) != '\0'; 
				++__newStrSize);
			this->copyString(newStr, __newStrSize);
		}

		explicit string(string const &newStr){
			unsigned long int __newStrSize = newStr.__size;
			this->__str = new char[newStr.__size + 1];
			this->copyString(newStr.str(), __newStrSize);
		}
		//Destructor
		~string(){
			if (this->__str) delete this->__str;
		}

		//Overloaded friend operators
		//"friend" can't be "explicit"
		friend std::ostream & operator <<(std::ostream &, string &);
		friend std::istream & operator >>(std::istream &, string &);
		string & operator =(char *__charVec){
			unsigned long int __newStrSize = 0;
			for (__newStrSize = 0; 
				*(__charVec + __newStrSize) != '\0'; 
				++__newStrSize);
			copyString(__charVec, __newStrSize);
			return *this;
		} 

		//Getter
		char *str() const{return this->__str;}
		
};

std::ostream &operator <<(std::ostream &ostrm, string &mystrn){
	ostrm << mystrn.str();
	return ostrm; 
};

std::istream &operator >>(std::istream &istrm, string &mystrn){
	unsigned long int bufferSize = 1, index = 0;

	if (mystrn.str())
		delete [] mystrn.str();

	//Just and alias
	char *buffer = new char[bufferSize], 
	*aux = NULL, c = 0;

	while(istrm.get(c) && c != 10){
		if (index == bufferSize){
			//realloc
			bufferSize *= 2;
			aux = new char[bufferSize + 1];
			unsigned long int i = 0;
			for(i = 0; i < index; ++i)
				*(aux + i) = *(buffer + i);
			*(aux + i) = '\0';
			delete buffer;
			buffer = aux;
			aux = NULL;
		}
		*(buffer + index++) = c;
	}

	mystrn = buffer;
	return istrm;
};

int main(int argc, char const *argv[]){
	string mySTr;
	std::cin >> mySTr;
	std::cout << mySTr << std::endl;
	return 0;
}