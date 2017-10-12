//Quotes source: https://www.tutorialspoint.com/java/java_interfaces.htm

//The abstract keyword here is legal, but extremely redundant, 
//as every java interface are, by definition, abstract by nature.
/*

middle linkage: http://stackoverflow.com/questions/2134200/why-declare-an-interface-as-abstract
9.1.1.1 abstract Interfaces:
Every interface is implicitly abstract. This modifier is obsolete and should not be used in new programs.

9.4 Abstract Method Declarations:
For compatibility with older versions of the Java platform, it is permitted but discouraged, 
as a matter of style, to redundantly specify the abstract modifier for methods declared in interfaces.	

Also:
	- Methods in any interface are implicity both public and abstract.
*/


/*abstract */interface MyInterface{
	//Implicity both public and abstract.

	//Can not have a constructor!
	//public abstract MyInterface();

	//Can ONLY be public!
	void genericMethod();

	//"Along with abstract methods, an interface may also contain 
	//constants, default methods, static methods, and nested types."

	//This can be done, because static/final.
	static final int x = 98;
	//This can be done, too.
	static float l = (float) 9.0;
	//And this.
	final double j = 9.8;
	//And this.
	int z = 9;
	//This not.
	//int s;
		//MyInterface.java:39: error: = expected
		//int s;

	/*
		Default method??
	*/

	//Inner class allowed.
	class MyInnerClass{

	};

	//Nested class allowed.
	static class MyNestedClass{

	};

	//Can not do define a method!
	/*void definedMethod(){
		System.out.println("Impose this behavior.");
	}

		MyInterface.java:26: error: interface abstract methods cannot have body
			void definedMethod(){
	*/


	//This, however, can be done with no problems.
	//That can be done for default methods, too. "Method bodies exist only for default methods and static methods."
	static void definedStaticMethod(){
		System.out.println("Impose this behavior, but this time with static keyword!");
	} 

};

/*
An Java interface seens pretty much like an abstract class,
with pure virtual methods in C++.
It serves do impose some default stardard that all his subclasses
must follow. "A class implements an interface".

"Along with abstract methods, an interface may also contain constants, 
default methods, static methods, and nested types. Method bodies exist 
only for default methods and static methods."

Like the C++ version, a interface cannot be instantiated and, unless a
sub-class define all the abstract methods, losing his "abstract label",
neither it can be instantiated.

- A interface, unlike C++ abstract class, can not have a constructor.
	-Try not![x]
- All the methods in an interface must be abstract (C++ pure virtual).
	- Try to declare and define one []
	- Try do declare and define a static one []
- Fields can onlyy be declared if defined at the same time.
	They can be static, final, local, static+final.
- A interface is not extended by a class, like inheritance does,
	and yes defined by a class.
	- Try the exactly oposite! []
- The concept of inheritance and multi-inheritance applies between interfaces.
	- Try it!/[]

*/