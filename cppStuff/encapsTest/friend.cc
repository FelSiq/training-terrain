#include <iostream>

class super{
	protected:
		int x;
	public:
		super(){
			x = 98;
		}
};

class myClassA : protected super{
	friend class myClassB;
	
	private:
		int x;

	protected:
		void almostSecret(){
			std::cout << "This is a protected method on A..." << std::endl;
		}
	public:
		virtual void print(){
			std::cout << "This is print on A..." << std::endl;
		}

		void methodA(){
			std::cout << "This is method on A..." << std::endl;
		}

		myClassA(){
			std::cout << "Created a instance of A..." << std::endl;
			this->x = super::x;
		}

		virtual ~myClassA(){}
};

class myClassB{
	friend void someFunction(myClassA *); 

	private:
		double y;
	public:
		void print(){
			std::cout << "This is print on B..." << std::endl;
		}

		static int grantXAcess(myClassA *instA){return instA->x;}

};

void someFunction(myClassA *instA){
	std::cout << myClassB::grantXAcess(instA) << std::endl;
}

int main(int argc, char const *argv[]){
	//EXPERIMENTS ON FRIEND CLASSES
	myClassA *secretInst = new myClassA;

	//test 1: Works fine
	someFunction(secretInst);
	//test 1: 
	
	delete secretInst;

	return 0;
}