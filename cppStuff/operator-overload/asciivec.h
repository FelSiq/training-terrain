#ifndef __ASCII_VEC_
#define __ASCII_VEC_

#include "string.h"

class asciivec {
	private:
		int *str;
		unsigned int size;

		asciivec(int *newStr, unsigned int newSize){
			this->str = new int[newSize]();
			this->size = newSize;
			for(unsigned int i = 0; i < newSize; ++i)
				*(str + i) = *(newStr + i);
		}

	public:
		//One of the constructors
		asciivec(){
			this->str = NULL;
			this->size = 0;
		}
		//Destructor
		~asciivec(){
			if (this->str != NULL)
				delete str;
		}

		//Getters
		unsigned int mySize() const{return this->size;}
		int *vec(){return this->str;}

		//Methods
		void print(){
			for(unsigned int i = 0; i < this->size; ++i)
				std::cout << *(this->str + i) << ' ';
			std::cout << std::endl;
		}

		//converter to another object
		//If we want to convert A to B,
		//or B to A, then both convertions
		//must be on the same object to avoid ambiguity

		//To do this, one function A (lib obj) -> B (this obj) must be a 
		//type converter, and B (this) -> A (lib) must be a constructor with
		//a B type argument.
		asciivec(string obj){
			char const *const aux = obj.get();
			this->size = strlen(aux);
			this->str = new int[this->size]();

			for (unsigned int i = 0; i < this->size; ++i)
				*(str + i) = *(aux + i);
		};

		operator string() const{
			char aux[this->size + 1];
			for (unsigned int i = 0; i < this->size; ++i)
				*(aux + i) = *(str + i);
			*(aux + this->size) = '\0';
			return string(aux);
		};

		//Overload + operator
		asciivec operator +(int x) const{
			asciivec temp(this->str, this->size);
			for(unsigned int i = 0; i < this->size; ++i)
				*(temp.vec() + i) += x;
			return temp;
		}
		//Same with - operator
		asciivec operator -(int x) const{
			asciivec temp(this->str, this->size);
			for(unsigned int i = 0; i < this->size; ++i)
				*(temp.vec() + i) -= x;
			return temp;
		}
};

#endif 