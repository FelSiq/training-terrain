#include <stdio.h>

/*
Conclusion: passing just the name of the function already passes it's address.
You may reference (&) and even deference it (*), but the effect remains the same 
(the addresses does not change).
*/

void someFunction() {
	// Does nothing.
}

int main(int argc, char * argv[]) {
	printf("Main address: %p\n", *main);
	printf("Main address: %p\n", main);
	printf("Main address: %p\n", &main);

	printf("Function address: %p\n", *someFunction);
	printf("Function address: %p\n", someFunction);
	printf("Function address: %p\n", &someFunction);
	return 0;
}
