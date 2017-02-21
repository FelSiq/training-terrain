#ifndef __MYSTRING_OVERLOAD_
#define __MYSTRING_OVERLOAD_

#include <cstring>

class string{
	private:
		char *str;

	public:
		//Constructors
		string(){this->str = NULL;}
		string(const char input[] = NULL){
			if (input != NULL){
				this->str = new char[strlen(input) + 1]();
				strcpy(this->str, input);
			} else this->str = NULL;
		};
		//Destructor
		~string(){
			if (this->str != NULL)
				delete this->str;
		};

		//Getter
		char *get() const{return this->str;}
		//Setter = overload operator "="
		void operator =(char const newInput[]){
			if (this->str != NULL)
				delete this->str;
			if (newInput != NULL){
				this->str = new char[strlen(newInput) + 1]();
				strcpy(this->str, newInput);
			} else this->str = NULL;
		}

		void operator =(string *stringB){
			if (this->str != NULL)
				delete this->str;
			if (stringB != NULL && stringB->get() != NULL){
				this->str = new char[strlen(stringB->get()) + 1]();
				strcpy(this->str, stringB->get());
			} else this->str = NULL;
		}

		void operator !=(string *stringB){
			if (this->str != NULL)
				delete this->str;
			if (stringB != NULL && stringB->get() != NULL){
				this->str = new char[strlen(stringB->get()) + 1]();
				strcpy(this->str, stringB->get());
				delete stringB;
			} else this->str = NULL;
		}

		//Methods w/ operators overload and polymorphism
		//==, <, >, >=, <=, +, +=

		//For pure string and char
		bool operator <(char const newInput[]) const{
			return (strcmp(this->str, newInput) < 0);
		}
		bool operator >(char const newInput[]) const{
			return (strcmp(this->str, newInput) > 0);
		}
		bool operator <=(char const newInput[]) const{
			return (strcmp(this->str, newInput) <= 0);
		}
		bool operator >=(char const newInput[]) const{
			return (strcmp(this->str, newInput) >= 0);
		}
		bool operator ==(char const newInput[]) const{
			return (strcmp(this->str, newInput) == 0);
		}
		string *operator +(char const B[]) const {
			char *auxstr = new char[strlen(this->str) + strlen(B) + 1]();
			strcpy(auxstr, this->str);
			strcat(auxstr, B);
			string *aux = new string(auxstr);
			delete auxstr;
			return aux;
		}
		string *operator +=(char const B[]){
			if (this->str != NULL)
				*this != (*(this) + (B));
			return this;
		}

		//For both strings
		//Same idea
		bool operator <(string *stringB) const{
			return (strcmp(this->str, stringB->get()) < 0);
		}
		bool operator >(string *stringB) const{
			return (strcmp(this->str, stringB->get()) > 0);
		}
		bool operator <=(string *stringB) const{
			return (strcmp(this->str, stringB->get()) <= 0);
		}
		bool operator >=(string *stringB) const{
			return (strcmp(this->str, stringB->get()) >= 0);
		}
		bool operator ==(string *stringB) const{
			return (strcmp(this->str, stringB->get()) == 0);
		}
		string *operator +(string *stringB) const {
			string *aux = new string(new char[strlen(this->str) + strlen(stringB->get()) + 1]());
			strcpy(aux->get(), this->str);
			strcat(aux->get(), stringB->get());
			return aux;
		}

		string *operator +=(string *stringB){
			if (this->str != NULL)
				*(this) != (*(this) + (stringB->get()));
			return this;
		}
};


#endif