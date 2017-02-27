#include <stdlib.h>
#include <stdio.h>
#include "static.h"

int *genericFunc(const int x){
	//static int myVar = x; wrong
	static int myVar = 5;
	myVar++;
	return &myVar;
}

int *genericFunc2(){
	static int *myPointer = NULL;

	if (myPointer == NULL){
		myPointer = malloc(4);
	}

	printf("%p\n", myPointer);
	return myPointer;
}

int main(int argc, char const *argv[]){
	/*int *myPointer = NULL,
	
	aux = atoi(*(argv + 1));
	
	int x = 10;

	while(0 < aux--){
		myPointer = genericFunc(x);
		printf("%p\n", myPointer);
	}

	printf("%d\n", *myPointer);*/

	/*
	Experiment results:
	
	Variables:
	- Static variables are only initialized ONCE (on the first call)
	- Its adress remains the same, so it was stored in global scope,
		but only acessible on local scope.
	- Static variables can only be initialized as true valued constants
		(not a primitive type casted to const type):
		int const x; static int myvar = x : wrong
		static int myvar = 10 : ok.
	-
	With pointers:
	- pointers can be static, just like primitive variables, however,
		you can't malloc on the pointer inicialization.
		output: initializer element is not constant.
	- You can modify then as much you want, and the adress of the heap memory
		region will be the same through the function calls.
	*/

	/*while(0 < aux--){
		myPointer = genericFunc2();
	}

	free(myPointer);*/

	//Fun fact:
	void (*aSecretFunction)(void) = exportSecretFunction();
	aSecretFunction();
	//Static functions can be exported to outside!!

	return 0;
}