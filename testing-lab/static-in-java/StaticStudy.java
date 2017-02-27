//Not permited
/*static class myStaticAuxClass{

}*/

class MyAuxClass{
	//Static variables can be acessed from anywhere
	//final static variables inside class needs to be initialized from here
	//final static int x = 6;
	//final static int x;
	final int x;

	//In java, you can instantiate your variables right on the declaration.
	//In fact, the java compiler WILL put this instantiations on ALL 
	//constructors of this class automatically.
	//The advantage is save code lines and never forget to initialize a single-initial-value 
	//variable if another constructor is needed afterwards.
	private double mySecretVariable = 9.5;

	/*
	Study static and non-static initializer blocks!
	*/

	//A static nested class can't 
	static class AuxNestedStaticClass{
		int k;
		void AuxInnerMethod(){
			System.out.print("This is AuxInnerStaticClass method.\n");
			//System.out.print("I'm static so I can not do this:" + mySecretVariable + "\n");
		}
	}

	//Inner class = Non-static nested class
	class AuxInnerClass{
		int k;
		void AuxInnerMethod(){
			System.out.print("This is AuxInnerNonStaticClass method.\n");
			System.out.print("I'm not static so I can do this: " + mySecretVariable + "\n");
		}
	}

	static void genericMethod(){
		System.out.print("This method can be called without any instance of MyAuxClass.\n");
	}

	MyAuxClass(){
		//Can't do that because its "static final"
		//But can do that if only "final", and non-static!
		x = 6;
	}


	/*
	"final" Must have been initialized in every construtor.
	MyAuxClass(int k){
		//Can't do that because its "static final"
		//But can do that if only "final", and non-static!
		//x = 8;
	}*/
}

//This is an java class!
enum javaGlobal{
	FALSE,
	TRUE
};

//Nor on main class of this source
class StaticStudy{
	//Works ok.
	static class MyStaticInnerClass{

		MyStaticInnerClass(){}
	}

	static private void genericMethod(){
		//Can't declare static variables inside methods on Java.

		/*static*/ int k = 6;

		MyAuxClass.genericMethod();
	}

	static public void main(String[] args){
		genericMethod();
		//Not even main can have static variables.
		//static int k;

		//You can only instantiate a Inner class with an existing instance of OuterClass
		MyAuxClass outerObj = new MyAuxClass();
		MyAuxClass.AuxInnerClass myInst = outerObj.new AuxInnerClass();
		myInst.AuxInnerMethod();

		//Static nested classes does not need the outerclass obj
		MyAuxClass.AuxNestedStaticClass myStaticInst = new MyAuxClass.AuxNestedStaticClass();
		myStaticInst.AuxInnerMethod();

		//System.out.print(genericMethod.k);
	}
};


/*

Static method:
	Can be called from everywhere (even from a non-static scope), 
	without any of the respective class instance.
*/




/*
Static classes:
- Only nested classes can be static in Java.
- A (non-static) inner class has acess of ALL DATA of its outer class (even PRIVATE DATA).
	A static nested class does not.
- The main reason of declaring a static nested class in Java is packing convenience
	and code clarity. In fact, a expected behavior of a static nested class and its
	outer class is exactly the same as two directly uncorrelated top-level classes. 

- An Innerclass can only be instantiated with and already existing instance of a Outerclass.
		MyAuxClass outerObj = new MyAuxClass();
		MyAuxClass.AuxInnerClass myInst = outerObj.new AuxInnerClass();
		myInst.AuxInnerMethod();

- An static nested class, however, can be instantiated without the outerclass instance:
	MyAuxClass.AuxNestedStaticClass myInst = new MyAuxClass.AuxNestedStaticClass();
	myInst.AuxInnerMethod();

NOTE:
"Nested classes are divided into two categories: static and non-static. 
Nested classes that are declared static are simply called static nested classes. 
Non-static nested classes are called inner classes. "

*/