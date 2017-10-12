
interface MyInterface{};
interface MyInterface2{};
interface MyInterface3 extends MyInterface, MyInterface2{};
class MyClass0 implements MyInterface3{};
class MyClass1 extends MyClass0{};
class MyClass2 extends MyClass1{};

class InstanceTest2{
	static public void main(String [] args){
		//One can instantiate a subclass with superclass pointer
		MyClass0 myInst0 = new MyClass1();
		MyClass0 myInst1 = new MyClass2();
		MyClass0 myInst2 = new MyClass0();

		//Instanceof is not restrictive. Actually, it checks if
		//the instace is, in fact, the class itself or a derivative
		//of it. Makes sense, as Inst1 are, in fact, a MyClass2,
		//MyClass1 and MyClass0 object.
		System.out.println(myInst2 instanceof MyInterface); // True
		System.out.println(myInst2 instanceof MyInterface2); // True
		System.out.println(myInst2 instanceof MyInterface3); // True
		System.out.println(myInst2 instanceof MyClass0); // True
		System.out.println(myInst2 instanceof MyClass1); // False
		System.out.println(myInst2 instanceof MyClass2); // False

		System.out.print("\n");

		System.out.println(myInst0 instanceof MyInterface); // True
		System.out.println(myInst0 instanceof MyInterface2); // True
		System.out.println(myInst0 instanceof MyInterface3); // True
		System.out.println(myInst0 instanceof MyClass0); // True
		System.out.println(myInst0 instanceof MyClass1); // True
		System.out.println(myInst0 instanceof MyClass2); // False
		
		System.out.print("\n");

		System.out.println(myInst1 instanceof MyInterface); // True
		System.out.println(myInst1 instanceof MyInterface2); // True
		System.out.println(myInst1 instanceof MyInterface3); // True
		System.out.println(myInst1 instanceof MyClass0); // True
		System.out.println(myInst1 instanceof MyClass1); // True
		System.out.println(myInst1 instanceof MyClass2); // True
	};
};