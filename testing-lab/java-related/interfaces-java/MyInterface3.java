//The apparently "collision" by merging MyInterface3 and MyInterface2 on MyMainClass,
//as both extends MyInterface, does not show any harm.
interface MyInterface3 extends MyInterface{
	//Try to override a method on another interface non-correlated
	//Guess it does not matter, as there's no definition details at all,
	//only the declaration.
	void genericMethod();
};