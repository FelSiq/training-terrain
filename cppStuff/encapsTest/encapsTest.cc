#include <iostream>

class foo{
	//1-a
	//2-a
	public:
		int b;
		int getA(){return a;}
		int getC(){return c;}

		int getSomething(){return getRes();}
		int somethingVeryVeryBoring(){return somethingMagical() - 49;}
		void qux(){std::cout << "Hell on world!" << std::endl;}
		//Public stuff:
		//can be called everywhere on the code,
		//just need a instance.
	private:
		int a;
		//Private stuff:
		int getRes(){return a + b;}
		//can only be called/used on this specific portion of code (from 1-a to 1-b)
	protected:
		int c;
		int somethingMagical(){return 49;}
		//Protected stuff:
		//can only be called inside this class or inside its childrens. (from 2-a to 2-b)
	//2-b
	//1-b
};

class bar: public foo{
	//2-a

	public:
		int somethingLessMagical(){return somethingMagical();}

	//2-b
};

/*

Public son: (Everything is keep the way father's have)
	father's public: still public.
	father's protected: still protected.
	father's private: not inherintable.

*/

/*
Protected son:
	father's public: turn protected.
	father's protected: still protected.
	father's private: not inherintable.
*/

/*
Private son:
	father's public: turn private.
	father's protected: turn private
	father's private: not inherintable.
*/
int main(int argc, char const *argv[]){
	foo *instance = new foo();

	instance->qux();	

	//a is private, but acessible from public message
	instance->getA();
	//b is public
	instance->b = 99;
	instance->getSomething();

	delete instance;
	return 0;
}