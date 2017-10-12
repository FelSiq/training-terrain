class myFinalTest{
	//Innerclasses
	class MyClass{
		protected void genericMethod(){
			//Do nothing...
		};

		//Constructor can't be "final"
		//final MyClass(){}
	};

	final class Subclass extends MyClass{
		protected void genericMethod(){
			//Do nothing 2...
		};

		//Fun-fact: neither on final subclass
		//final Subclass(){}
	};

	static public void main(String args[]){
		/*
		final int k;
		k = 7;
		k = 9;
		*/
		
		/*
		final MyClass inst;
		inst = new MyClass();
		inst = null;
		*/
	}
};


/*
Hypotesis: The "final" keyword in java has three basic meanings:

object/pointer: the object can be initialized only once 
	and then its value cannot be changed anymore.
	Similar to a const variable in C/C++.

- final members of a class must have been initialized on ALL constructors of the class 
		final.java:4: error: variable myVar not initialized in the default constructor
				final int myVar;
		final.java:8: error: variable myVar might not have been initialized
				}
- If they are not inside a class body, then you don't not to initialize a final
	object/pointer on its declaration.
	//Example 1
		final int k; //ok, does not need to be initialized already.
		k = 7; //ok, initialization
		k = 9; //wrong, already initialized!
	//Example 2
		final MyClass inst; //ok 
		inst = new MyClass(); //ok 
		inst = null; //	can't do that!


-------------------------------------------------------------
Method: the method cannot be overriden by any subclasses methods.
	final.java:10: error: genericMethod() in myFinalTest.Subclass cannot override genericMethod() in myFinalTest.MyClass
			protected void genericMethod(){
			               ^
	  overridden method is final
- Constructors can't be final, even on final classes

-------------------------------------------------------------
Class: this class ends the inheritance process on its branch, i.e it cannot be inherited.
	final.java:7: error: cannot inherit from final myFinalTest.MyClass
		class ShouldNotWork extends MyClass{

*/