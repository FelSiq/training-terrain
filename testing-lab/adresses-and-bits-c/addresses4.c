#include <stdlib.h>
#include <stdio.h>

#define VEC_SIZE 10

void clear_vector(int vector[], int vec_size){
	int *p;
	for (p = vector; p < &vector[vec_size]; ++p)
		*p = (unsigned int) ((void *) p - (void *)vector);
}

void print_vector(void * const vector, int vec_size){
	void const *p;
	for (p = vector; p < (vector + vec_size * (sizeof(int))); p += sizeof(int))
		printf("%d ", *(int *)p);
	printf("\n");
}

int main(int argc, char const *argv[]){
	int vector[VEC_SIZE];

	auto void (*p1)(int *, int) = &clear_vector;
	auto void (*p2)(void *, int) = &print_vector;
	
	p1(vector, VEC_SIZE);
	p2(vector, VEC_SIZE);

	return 0;
}