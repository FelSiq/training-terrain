#include <stdio.h>

int k;

int main(int argc, char const *argv[]){
	static int i = 0;
	int j = 3;

	printf("Adress of i - j: %ld\n", &i - &j);
	//Both integers (or int const) = -1
	//When i static: -35181161929504
	//When j static: 35183862410677
	//When both static: 2

	printf("Distance (in Giga integers) of i and argc: %ld\n", (&i - &argc)/(1024*1024*1024));
	printf("Adress of j - argc: %ld\n", &j - &argc);
	/*
	When both integers:
		Adress of i - argc: 1
		Adress of j - argc: 2
	When static:
		A big inexpressive NEGATIVE number (-35181281111078)
	*/

	printf("Adress of (global) k - (static) i: %ld\n", &k - &i);
	/*
	Adress of (global) k - (static) i: 1
	*/

	/*
	Result: 1. global and static variables are stored on the same memory chunk.
			2. global and static variables are stored FAR 
				BEFORE on STACK of local variables (roughly 3.27e+13 integers of distance)

	*/

	return 0;
}