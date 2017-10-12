#include <stdlib.h>
#include <stdio.h>
#include <time.h>

//#define SIZEVEC 5

//typedef unsigned int ulli;

//Manipulated to not overflow
//#define MYSTACKSIZE 8300000

typedef unsigned char someType; 

typedef struct{
	someType trueBoolean0:1;
	someType trueBoolean1:1;
	someType trueBoolean2:1;
	someType trueBoolean3:1;

	someType trueBoolean4:1;
	someType trueBoolean5:1;
	someType trueBoolean6:1;
	someType trueBoolean7:1;

	someType trueBoolean8:1;
	someType trueBoolean9:1;
	someType trueBoolean10:1;
	someType trueBoolean11:1;

	someType trueBoolean12:1;
	someType trueBoolean13:1;
	someType trueBoolean14:1;
	someType trueBoolean15:1;

	someType trueBoolean16:1;
	someType trueBoolean17:1;
	someType trueBoolean18:1;
	someType trueBoolean19:1;

	someType trueBoolean20:1;
	someType trueBoolean21:1;
	someType trueBoolean22:1;
	someType trueBoolean23:1;

	someType trueBoolean24:1;
	someType trueBoolean25:1;
	someType trueBoolean26:1;
	someType trueBoolean27:1;

	someType trueBoolean28:1;
	someType trueBoolean29:1;
	someType trueBoolean30:1;
	someType trueBoolean31:1;

	//someType trueBoolean32:1;
} myStruct;

int main(int argc, char const *argv[]){
	//long long int adress;

	/*int *heapVec = malloc(sizeof(int) * SIZEVEC);
	int stackVec[SIZEVEC];

	int *heapVec2 = malloc(sizeof(int) * SIZEVEC);
	int stackVec2[SIZEVEC];

	for (int i = 0; i < (SIZEVEC); ++i){
		adress = (signed) ((long unsigned) (heapVec + i) - (long unsigned) (heapVec2 + i));
		printf("heapdVec - heapVec2: %lld\t", adress);
		adress = (signed) ((long unsigned) (stackVec + i) - (long unsigned) (stackVec2 + i));
		printf("stackVec - stackVec2: %lld\n", adress);
	}

	free(heapVec);
	free(heapVec2);
	*/

	/*
	Result: om my architecture (x86_64 x86_64 x86_64 GNU/Linux), 
	compiler (gcc (Ubuntu 5.4.0-6ubuntu1~16.04.4) 5.4.0 20160609) 
	and OS (Ubuntu 16.04),
	both results are negative, i.e, both heap and stack are descendant.
	*/
	//ulli index;

	/*clock_t start, end;
	double resStack, resHeap;

		start = clock();
		char stackVec[MYSTACKSIZE];
		end = clock();
		printf("stack allocation: %lf\n", resStack = ((end - start)/(1.0 * CLOCKS_PER_SEC)));

		start = clock();
		char *heapVec = malloc(sizeof(char) * MYSTACKSIZE);
		end = clock();
		printf("heap allocation: %lf\n", resHeap = ((end - start)/(1.0 * CLOCKS_PER_SEC)));
		
		*stackVec = 0;

		printf("H/S: %lf\n", 100 * ((resHeap)/(resStack)));

		free(heapVec);*/

	/*
		stack allocation: 0.000002
		heap allocation: 0.000010
		H/S: 500.000000
		
		stack allocation: 0.000002
		heap allocation: 0.000011
		H/S: 550.000000
		
		stack allocation: 0.000001
		heap allocation: 0.000010
		H/S: 1000.000000
		
		stack allocation: 0.000002
		heap allocation: 0.000009
		H/S: 450.000000
		
		stack allocation: 0.000002
		heap allocation: 0.000011
		H/S: 550.000000

		stack allocation: 0.000002
		heap allocation: 0.000009
		H/S: 450.000000
		
		stack allocation: 0.000001
		heap allocation: 0.000016
		H/S: 1600.000000
		
		stack allocation: 0.000002
		heap allocation: 0.000010
		H/S: 500.000000
		
		stack allocation: 0.000002
		heap allocation: 0.000015
		H/S: 750.000000
		
		stack allocation: 0.000002
		heap allocation: 0.000024
		H/S: 1200.000000

	//Conclusion: memory allocation on heap can be roughly ~800 times slower than stack allocation.
	
	*/

	/*
	for(index = 0; index < MYSTACKSIZE; ++index);

	start = clock();
	for(index = 0; index < MYSTACKSIZE; ++index)
		*(heapVec + index) = 48;
	end = clock();

	printf("heap time: %lf\n", (end - start)/(1.0 * CLOCKS_PER_SEC));
	
	start = clock();
	for(index = 0; index < MYSTACKSIZE; ++index)
		*(stackVec + index) = 48;
	end = clock();
	printf("stack time: %lf\n", (end - start)/(1.0 * CLOCKS_PER_SEC));
	
	output:
		heap time: 0.104444
		stack time: 0.124457
	free(heapVec);


	Conclusion: access on Heap can be even faster than stack memory, if SEQUENTIAL on memory.
	*/

	printf("%lu\n", sizeof(myStruct));
	//With x trueBoolean : sizeof(myStruct)
	//INTEGERS (BOOLEAN PACKAGES):
		//1 : 4
		//31 : 4
		//32 : 4
		//33 : 8		
	//CHAR (TRUE BOOLEAN INDEED):
		//1 : 1
		//8 : 1
		//9 : 2
		//16: 2
		//17: 3
		//32 : 4
		//33 : 5

	return 0;
}