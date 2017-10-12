//Need to use the "implements" keyword to assume a interface.

//A class can only extends one class¹, but can implement a bunch of interfaces
//A interface can extend another interface, and be extended by a bunch of interfaces

//Implementing multiple interfaces
class MyMainClass implements MyInterface2, MyInterface3{

	//Override the abstract method os MyInterface
	//Must be public
		//MyMainClass.java:5: error: genericMethod() in MyMainClass cannot implement genericMethod() in MyInterface
		//void genericMethod(){
	    //	   ^
 	 	//attempting to assign weaker access privileges; was public

	//Must be exactly the same in modifier (public), return value and 
	//parameters (this case, noone) as in the interface.
	public void genericMethod(){
		
	}

	public int genericMethod2(){
		return 5;
	}

	//New methods can be implemented
	public void myNewMethod(FourrierTransform something){

	}
	//New variables with different qualifiers and types too.
	private int k;
	protected float z;
	public String theta; 

	public static void main(String[] args) {
		
	}
};

/*
¹: Java does not support multiple inheritance.

class MyAuxClass1{};
class MyAuxClass2{};
//Does not work.
class MergingMyAuxs extends MyAuxClass1, MyAuxClass2{};

	MyMainClass.java:39: error: '{' expected
	class MergingMyAuxs extends MyAuxClass1, MyAuxClass2{
	                                       ^
	1 error
*/