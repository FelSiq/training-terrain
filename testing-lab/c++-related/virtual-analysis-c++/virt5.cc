#include <iostream>

class person{
	public:
		void print(){
			std::cout << "This is Person's class print..." << std::endl;
		}

		virtual ~person(){}
};

class student : public person{
	public:
		virtual void print(){
			std::cout << "This is Student's class print..." << std::endl;
		}
};

class felipe : public student{
	public:
		void print(){
			std::cout << "This is Felipe's class print..." << std::endl;
		}
};


class myClassX{
	public:
		virtual void print(){
			std	::cout << "test" << std 	::	endl; 
		}
};

class myClassY : public myClassX{
	public:
		void print(){
			//Do nothing again
			std :: cout << "test2" << std:: 	endl;
		}
};

int main(int argc, char const *argv[]){
	//person *instP = new person;
	//student *instT = new student;
	student *instF = new felipe;

	//instP->print();
	//instT->print();


	//Works fine.
	instF->student::print();
	//Superclass virtual functions can still be called on subclasses
	std::cout << sizeof(myClassX) << "/" << sizeof(myClassY) << std::endl;
	//no virtual out: 1/1
	//virtual out: 8/8
	//This proves that the subclass has BOTH functions, despite the fact that
	//superclass function is virtual. Virtual only makes pointers "inteligent"
	//At certain situations.
	//Maybe on multi-inherited subclass derivated of two or more subclasses,
	//that are derivatives of a common superclass, does not have the
	//"second" copy of this last superclass overwrited, but maybe
	//the "virtual class" things just warns the compiler to not do
	//stuff that creates ambiguity.

	//delete instP;
	//delete instT;
	delete instF;

	return 0;
}