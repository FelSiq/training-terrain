#include <stdio.h>
#define VEC_SIZE 9999999999999

 inline void calculate(int *a, int *b){
	*a = *b % 3;
}

int main(int argc, char const *argv[]){
	int a = 0, b = 0;
	for (register size_t i = 0; i < VEC_SIZE - 1; ++i)
		calculate(&a, &b);
	printf("%d\n", a);
	return 0;
}