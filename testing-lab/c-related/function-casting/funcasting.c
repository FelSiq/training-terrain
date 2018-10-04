#include <stdio.h>

int func(int a, float b, char c) {
	if (a == 0) 
		printf("%f %c\n", b, c);
	else if(a > 0)
		printf("%f\n", b);
	else
		printf("Hello world! %f\n", a);
}


/*
	How to call the same function with a variable
	number of arguments.
*/

int main(int argc, char *argv[]) {

	// Using correct auxiliary pointer
	int (*p1)(int, float, char) = func;	
	p1(0, 0.5, 'f');

	// Using incorrect auxiliary pointer
	int (*p2)(int, float) = func;	
	p2(1, 0.5);

	// Using direct casting
	((int (*)(int, float)) func)(1, 0.5);

	// Still using direction casting + type changing
	((int (*)(float)) func)(-1.5);

	return 0;
}
