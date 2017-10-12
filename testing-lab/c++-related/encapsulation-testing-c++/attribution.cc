#include <iostream>

class myClass{
	int a, b;
	protected:
		int c;
	public:
		myClass(){
			a = 1;
			b = 2;
			c = 3;
		}
		//Getters just for test purposes
		int getA(){return a;}
		int getB(){return b;}
		int getC(){return c;}
		//Setters for test
		void setA(int A){a = A;}
		void setB(int B){b = B;}
		void setC(int C){c = C;}
};

class mySon: public myClass{
	int d;
	float e;
	public:
		//Will call myClass() by default
		mySon(){
			d = 4;
			e = 5;
		};

		int getD(){return d;}
		int getE(){return e;}


		void setD(int D){d = D;}
		void setE(int E){e = E;}
};

class identicalSon: public myClass {};

int main(int argc, char const *argv[]){
	myClass k;
	mySon t;

	identicalSon m;

	//Raw tests
	//does not work (derived class = superclass)
	//t = k;

	//Not even a identical son works with (derived class = superclass)
	//m = k;

	std::cout  << k.getA() << "/" 
		<< k.getB() << "/" 
		<< k.getC() << std::endl;

	//Works fine (superclass = derived class)
	k = t;

	t.setA(7);
	t.setB(7);
	t.setC(7);
	std::cout  << k.getA() << "/" 
		<< k.getB() << "/" 
		<< k.getC() << std::endl;

	return 0;
}