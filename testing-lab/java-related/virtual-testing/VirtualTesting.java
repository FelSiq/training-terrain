class classA{
	private int x;
	public void myFunc(){
		System.out.print("This is classA function...\n");
	}
	public void genericFunc(){
		System.out.print("This is as genericFunc of A...\n");
	}
};

class classB extends classA{
	private int x;
	public void myFunc() {
		System.out.print("This is classB function...\n");
	}
	public void anotherFunc(){
		System.out.print("This is as genericFunc of A...\n");
	}
};

class classC extends classB{
	private int x;
	public void myFunc() {
		super.myFunc();
		System.out.print("This is classC function...\n");
	}
};

class VirtualTest{
	static public void main(String args[]){
		//On inherit pointers, the superclass pointer can point 
		//to either a subclasses or its class aswell.
		//in fact, a subclass is a superclass instance.
		//However, subclass pointer can't point to a
		//superclass, because, in fact, superclass is not a subclass type.

		//In java, every declaration that is not a primitive type
		//is a implicit declaration of a pointer.

		//Hypotesis: all methods in java are virtual in nature.

		/*
		Test 1: A pointer to a B.
		expects: class B method.
		output: This is classB function...

		Test 2: A pointer to a C.
		expects: class C method.
		output: This is classC function...

		Test 3: try to call polymorphed method classA::myFunc() from
		method anotherFunc() of B.
		result: works. Super does not need to be on the first line,
			only on constructors.
			Works fine on the polymorphed method classB::myFunc() too.
		*/
		classB pointer = (classB) new classB();

		pointer.myFunc();
	}
};