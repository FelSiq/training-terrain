class MyAuxClass{
	private int myX;
	class MyAuxInnerClass{
		//C++ "Friend" behaviour
		int k;
		public int getX(){return myX;} 
	};
	static class MyAuxNestedClass{};

	//Won't work. Still the unidirectional "friend" behaviour of C++
	//public int getk(){return k;}
};

class MySubClass extends MyAuxClass{
	class MySubClassInnerClass{};
	static class MySubClassNestedClass{};
};

interface MyInterface{};
class MyInterfaceClass implements MyInterface{};
class MyInterfaceSubClass extends MyInterfaceClass{};
/*

	Remember: nested static classes does not need a instance of outer classes
	in order to be instantiate. Inner classes does.

	No instantiate a inner class:

	OuterClass.InnerClass inst = OuterClass.new InnerClass(<params>);


*/

class InstanceOfTeste{


	public static void main(String [] args){
		//Superclass
		MyAuxClass inst0 = new MyAuxClass();
		MyAuxClass.MyAuxInnerClass inst1 = inst0.new MyAuxInnerClass();
		MyAuxClass.MyAuxNestedClass inst2 = new MyAuxClass.MyAuxNestedClass();

		//Subclass
		MySubClass inst3 = new MySubClass();

		MySubClass.MySubClassInnerClass inst4 = inst3.new MySubClassInnerClass();
		MySubClass.MySubClassNestedClass inst5 = new MySubClass.MySubClassNestedClass();

		//Interface class
		MyInterfaceClass inst6 = new MyInterfaceClass();
		MyInterfaceSubClass inst7 = new MyInterfaceSubClass();

		//Testing
		System.out.println(inst0 instanceof MyAuxClass); //true

		//These two can't even be tested
		//System.out.println(inst0 instanceof MyAuxClass.MyAuxInnerClass);
		//System.out.println(inst0 instanceof MyAuxClass.MyAuxNestedClass);
		/*
			InstanceOfTeste.java:45: error: incompatible types: MyAuxClass cannot be converted to MyAuxClass.MyAuxInnerClass
				System.out.println(inst0 instanceof MyAuxClass.MyAuxInnerClass);
				                   ^
			InstanceOfTeste.java:46: error: incompatible types: MyAuxClass cannot be converted to MyAuxNestedClass
					System.out.println(inst0 instanceof MyAuxClass.MyAuxNestedClass);
					                   ^
			2 errors
		*/
		//Can't be tested either
		//System.out.println(inst1 instanceof MyAuxClass);

		//error
		//System.out.println(inst1 instanceof MyAuxClass.MyAuxNestedClass);

		//error
		//System.out.println(inst3 instanceof MyAuxClass.MyAuxInnerClass);

		//error
		//System.out.println(inst3 instanceof MyAuxClass.MyAuxNestedClass);
		
		//error
		//System.out.println(inst4 instanceof MyAuxClass);
		
		//error
		//System.out.println(inst5 instanceof MyAuxClass);
		
		//error
		//System.out.println(inst3 instanceof MySubClass.MySubClassInnerClass);

		System.out.println(inst0 instanceof MySubClass);//false
		System.out.println(inst3 instanceof MyAuxClass);//true

		//Works and is true
		System.out.println(inst6 instanceof MyInterface);//true
		System.out.println(inst7 instanceof MyInterface);//true
		System.out.println(inst7 instanceof MyInterfaceClass);//true
	}
};


/*

	FINAL CONCLUSION:
	
	the instanceof operator works ONLY on classes DIRECTLY INHERINTED, i.e
	which is actually possible create a "pointer" A which points to B-extends-A.
	In other words, instaceof keyword is ONLY allowed when there's a possibility
	of a TRUE scenario.

	Nested/Inner classes does not have any Inheritation property (aside from a "friend" behavior),
	and InnerClass instaceof OuterClass, or vice-versa, leads to a compilation error.

	This works with interfaces too, as interfaces are actually pure abstract classes:
		ClassImplementedWInterface instanceof Interface//legal and true

*/