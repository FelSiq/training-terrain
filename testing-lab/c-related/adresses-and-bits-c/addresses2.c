#include <stdlib.h>
#include <stdio.h>

//FOR RESULTS, GO TO LINE 262

//int fastGlobal;
//int firstGlobal;
//int secGlobal = 1;
//int *globalPointer;

#define __VECSIZE 10
typedef int atype;

void finalFunc(int *stackvector1, int *stackvector2){
	int stackvector3[__VECSIZE];

	//Expected result:
	//Address of A is smaller than B
	//Both A and B have greater addresses than C
	printf("\t[STACK TEST] stackvector3 - stackvector1: %ld\n", stackvector3 - stackvector1);
	//Negative result
	printf("\t[STACK TEST] stackvector3 - stackvector2: %ld\n", stackvector3 - stackvector2);
	//Negative result even smaller

	/*int a;
	printf("<EXTRA TEST> a adress: %ld\n", (long int) &a);
	globalPointer = &a;
	*/
}

void anotherFunc(int *a, int *k){
	int z = 0;
	printf("\t[STACK TEST] (aFunc) z - (main) a: %ld\n", &z - a);
	//Negative value
	printf("\t[STACK TEST] (aFunc) z - (gFunc) k: %ld\n", &z - k);
	//Negative value (even more)
	//Expected result: both negative numbers
	//Conclusion: stack addresses expands DESCENDINGLY
	//	i.e, as much stack you need, the smaller will be the addresses.
	//	However, there's a limit: stack is far below the heap reagion of
	//	the program are.
	//
	//ADRESSES:
	//			---------------------
	//	0		|					|
	//			---------------------
	//	1		|					|
	//			---------------------
	//	2		|					|
	//			---------------------
	//	3		|	\/	HEAP \/		|	Interfunction, the addresses in stack  
	//			---------------------	keeps decreasing.
	//	4		|					|	The heap addresses always (either inter or
	//			---------------------	intra function increseases, unless a
	//	...		|					|	heap chunk is freed and can be used again
	//			---------------------	to fit the hole. If possible, it probably 
	//	n-3		|					|	will).
	//			---------------------
	//	n-2		|					|
	//			---------------------
	//	n-1		|					|
	//			---------------------
	//	n		|	/\	STACK /\	|
	//			---------------------
	//
	//	intra-function:
		//-------------------
		//|	Function 2		| 0
		//-------------------
		//|	First var		| 1		Inside a function, stack addresses
		//-------------------		increseases.
		//|		...			| ...	Inter-functions, the addresses
		//-------------------		decreseases.
		//|	Function 1		| 41
		//-------------------
		//|	First var		| 42
		//-------------------
		//|	Second var		| 43
		//-------------------
		//|		...			| ...
		//-------------------
		//|		Main		| 158
		//-------------------
		//|	First var		| 159
		//-------------------
		//|	Second var		| 160
		//-------------------
		//|	third variable	| 161
		//-------------------
		//|		...			| ...
		//-------------------

	int stackvector1[__VECSIZE];
	int stackvector2[__VECSIZE];

	//results:
	// sv1 - sv2 = negative number.(addresses INTRA-FUNCTION ARE ASCENDING)
	printf("\t[STACK TEST] (before) stackvector1 - (after) stackvector2: %ld\n", stackvector1 - stackvector2);
	finalFunc(stackvector1, stackvector2);

	//INTRA-VECTOR?
	printf("\t[STACK TEST] Address of:\n\tStackVec1:\tStackVec2:\n");
	for(size_t i = 0; i < __VECSIZE; ++i)
		printf("\t%p\t%p\n", (stackvector1 + i), (stackvector2 + i));
	//Result: Intra-vector, even stack vectors are ascendingly
}

//int slowGlobal = 1;

atype *genericFunc(int *a){
	int k = 99; //Address smaller than #1, #4 and #3
	int j; //Address smaller than #1 and #4, but greater than #3

	printf("\t[STACK TEST] Address of variable #2: %p\n", &k);
	printf("\t[STACK TEST] Address of variable #3: %p\n", &j);
	printf("\t[STACK TEST] (main) a - (gFunc) k: %ld\n", a - &k);
	//	[STACK TEST] (main) a - (gFunc) k: 12, then adress of a is 12 integers LARGER than k 

	anotherFunc(a, &k);

	//printf("<EXTRA TEST> k adress: %ld\n", (long int) &k);
	//printf("<EXTRA TEST> globalPointer - local (gFunc): %.0LF\n",
	//	sizeof(long double)/sizeof(int) * (long double) (globalPointer - &k));

	return malloc(sizeof(atype) * __VECSIZE);
}

int main(int argc, char const *argv[]){
	int a;//Address greather than #2 and #3 but smaller than #4 (in main too) 
	printf("\t[STACK TEST] Address of variable #1: %p\n", &a);

	atype *vectorA = malloc(sizeof(atype) * __VECSIZE);
	atype *vectorB = genericFunc(&a);
	atype *vectorC = malloc(sizeof(atype) * __VECSIZE);

	int l;
	printf("\t[STACK TEST] Address of variable #4: %p\n", &l); //The greater adress of all four variables

	printf("[HEAP TEST] Address of:\nvectorA:\tvectorB:\tvectorC:\n");
	for(size_t i = 0; i < __VECSIZE; ++i)
		printf("%p\t%p\t%p\n", (vectorA + i),
			(vectorB + i), (vectorC + i));

	printf("[HEAP TEST] adressA - adressB = %ld\n", vectorA - vectorB);
	printf("[HEAP TEST] adressA - adressC = %ld\n", vectorA - vectorC);
	printf("[HEAP TEST] adressB - adressC = %ld\n", vectorB - vectorC);
	//Vecsize = 10 -> Each vector has a difference of 12 bytes of each other
	//Vecsize = 16 -> ""	""	"" 16 bytes ""
	//Vecsize = 16 -> 20 bytes of diff 
	//Conclusion: malloc uses more memory than actually allocated

	//Values between vectorA and vectorB
	/*
	int *aux = vectorB;
	for(size_t i = 11; i > 0; --i)
		printf("[HEAP TEST] AUX adress: %p\tVALUE: %d\n",  (int *) ((long int) aux - i), *aux);
	*/
	
	free(vectorB);
	printf("Freed vectorB...\n");
	int *testHeap = malloc(sizeof(int) * __VECSIZE + 1);
	printf("[HEAP TEST] Address on final heap chunk: %p\n[HEAP TEST] final - C: %ld\n", 
		testHeap, testHeap - vectorC);
	//If not freed vectorB, Output 48 (12 integers below, as always)
	//If B freed and final same size or LESS, result will be 12 integers above
	//If size does not fit (size is STRICTLY GREATER, even by one byte), then 12 integers below again
	

	//If testHeap1 does not fit the "hole" of vectorB, then, if testHeap2 can, he will. 
	//If testHeap1 does fit the "hole" of vectorB, then testHeap2 will be 12 integers below vectorC.
	//If neither testHeap1 and testHeap2 can fit, then testHeap2 will point to somewehere 
	//below of testHeap1.
	int *testHeap2 = malloc(sizeof(int) * __VECSIZE + 1);
	printf("[HEAP TEST] Address on final heap chunk: %p\n[HEAP TEST] final - C: %ld\n", 
		testHeap2, testHeap2 - vectorC);	

	free(testHeap2);
	free(testHeap);
	free(vectorA);
	free(vectorC);
	//VectorB already freed

	/*
	extra footage:
	*/
	/*
	printf("Function adresses:\nMain: %p\ngFunc: %p\naFunc: %p\nfFunc: %p\n", 
		main, genericFunc, anotherFunc, finalFunc);
	*/
	/*	
	output:
		Main: 0x40089d << greatest
		gFunc: 0x4007f8
		aFunc: 0x4006e4
		fFunc: 0x400666 << smallest
	Definition of functions follows a ASCENDINGLY ORDER (main is the "last" one)
	*/

	/*
	extra-extra footage:
	*/
	
	/*
	Extra test: does initialization of global/static variables actualy effect its adresses?
	*/

	//printf("<EXTRA> firstGlobal - secGlobal: %ld\n", &firstGlobal - &secGlobal);
	//outputs:
	//both uninitialized: 1 
	//just 1st initialized: -3
	//just 2st initialized: 3
	//both initialized: -1
	//Answer: yes, initialization does affect innitial adress of variable.
	//	A non-initialized value are on BSS data segment, which is BELOW the initialized segment.

	//static int uglyStaticVariable;
	/*
	printf("Global adresses:\nfast: %p\nslow: %p\nstatic: %p\nmain - fast: %ld\nmain - slow: %ld\n",
		&fastGlobal, &slowGlobal, &uglyStaticVariable, 
		(long int)((int *) main - (int *) fastGlobal), 
		(long int) ((int *) main - (int *) slowGlobal));
	*/
	/*
	outs:
		fast: 0x602058
		slow: 0x60205c
		static: 0x602064
		main - fast: 4196507
		main - slow: 4196508

	The code memory chunk is FAR bwlow the global and static variables 
	(those last ones are actually put almost together).
	*/

	/*
	extra-extra-extra footage:
	*/
	//printf("<EXTRA>\naddress of argc: %p\nadress of argv: %p\ndiff (c - v): %ld\ndiff (c - a): %ld\ndiff (v - a): %ld\n", 
	//	&argc, argv, (int *) &argc - (int *) argv, &argc - &a, (int *) argv - (int *) &a);
	//300 bytes of difference, negative value (i.e argv comes AFTER argc)
	//This value does not seen to be modified with different number of arguments

	/*
	outs:
		diff (c - v): -75 //argv are 75 integers below argc
		diff (c - a): -1 //The first variable are on right on four bytes below argc
		diff (v - a): 74 //Then, obviously, argv are 74 integers below first variable. 
	*/

	/*
	printf("<EXTRA-EXTRA>\nmain - argv: %.0LF\nmain - argc: %.0LF\n",
		sizeof(long double)/sizeof(int) * (long double) ((long double *) main - (long double *) argv), 
		sizeof(long double)/sizeof(int) * (long double) ((long double *) main - (long double *) &argc));
	*/

	/*
		main - argv: -35181983136395
		main - argc: -35181983136320
		difference: 3.276578e+13 integers (or 1.407279e+14 bytes) of real memory diff
		conclusion: there's a ridiculously difference between the last function code adress
			(main) and the argc/argv.
	*/

	/*
	printf("stackVar - argv: %.0LF\nstackVar - static: %.0LF\nstackVar - local (main): %.0LF\n", 
		sizeof(long double)/sizeof(int) * (long double) (globalPointer - (int *) argv), 
		sizeof(long double)/sizeof(int) * (long double) (globalPointer - &uglyStaticVariable), 
		sizeof(long double)/sizeof(int) * (long double) (globalPointer - &a));

	*/
	/*
	output:
		stackVar - argv: -588
		stackVar - static: 140729790002248
		stackVar - local (main): -292

	*/
	return 0;
}

	//####################################################################
	//General result: 
	//	1. New HEAP memory chunks addresses is ASCENDINGLY (adress increseases)
	//	2. intra-vector, the HEAP vectors addresses are still ASCENDINGLY (adress increseases)
	//	3. STACK addresses are ASCENDINGLY intra-function (on the same function) (adress increseases)
	//	4. intra-vector, the stack vectors addresses are ASCENDINDLY (adress increseases)
	//	5. inter-funtions (between functions), STACK expands DESCENDINGLY (adress shrinkes)

	//Final conclusion: in general, adresses always increseases in relation of the
	//previous adress. The only apparent exception (excluding special cases like global/static 
	//variables) is the STACK ADRESSES between FUNCTION CALLS, that DECRESEASES.
	////####################################################################

//	Merely illustrative:
// 	ADR	FINAL CONCLUSIONS:
//		-------------------------	\
//	901	|ARGV					|	| Curiosity: by default argv is aprox. 250 bytes
//		-------------------------	|            below argc, with a "empty" main.
//	900	|MAIN FUNC VARIABLES 	|	|			 argv is always the last adress of the program.
//		-------------------------	|
//	898	|ARGC					|	|- STACK memory (Ascending inner-function)
//		-------------------------	|				(Descending between functions)
//	897	|STACK REMAIN \/\/\/\/	|	|
//		-------------------------	...
//	...	|						|	|
//		-------------------------	|	
//	...	|						|	/
//		-------------------------	\
//	...	|						|	| Curiosity:	malloc actually always need more
//		-------------------------	| 				bytes than you ask for.
//	...	|						|	|				
//		-------------------------	|- HEAP space for allocation (always ascending,
//	...	|						|	|	unless a chunk is freed and the new one
//		-------------------------	|	fits its size).
//	18	|HEAP CHUNKS /\/\/\/\	|	|
//		-------------------------	/
//	17	|BSS (G/S UNINITIALIZED)|
//		------------------------- <- This is why uninitialized global data comes after (below) on RAM
//	16	|G/S VARS INITIALIZED 	|
//		------------------------- 	\
//	15	|MAIN FUNCTION CODE		| 	| Curiosity:	The definition order of the functions
//		------------------------- 	|				on source code is mantained here. 
//	...	|		...				| 	| 				Declaration order does not affect here.
//		------------------------- 	|
//	1	|SECOND FUNCTION CODE	| 	|- MACHINE CODE
//		------------------------- 	|
//	0	|FIRST FUNCTION CODE	| 	|
//		-------------------------	/

