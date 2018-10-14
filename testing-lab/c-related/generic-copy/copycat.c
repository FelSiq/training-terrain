#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/*
	Code showing how to copy data from a void *
	souce to a generic destiny using just the
	size of the source as extern information.
*/

// Way 1
void generic_copy1(void *dest, void *src, size_t size) {
	unsigned char *aux_a = dest;
	unsigned char *aux_b = src;

	for (register size_t i = 0; i < size; i++) {
		aux_a[i] = aux_b[i];
	}
}

// Way 2
void generic_copy2(void *dest, void *src, size_t size) {
	register size_t i = 0;
	while (i < size) {
		*(unsigned char *)(dest + i) = *(unsigned char *)(src + i);
		i++;
	}
}

// Way 3
void generic_copy3(void *dest, void *src, size_t size) {
	memcpy(dest, src, size);
}

// Testing section
typedef int type_test;
#define printf_mask "%d\n"
#define loop_rep (size_t) 1000000000

int main(int argc, char *argv[]) {

	type_test src = ((unsigned) -1) >> 1;
	type_test dest;

	for (register size_t j = 0; j < loop_rep; j++) 
		generic_copy1(&dest, &src, sizeof(type_test));

	printf(printf_mask, dest);

	return 0;
}


/*
EXECUTION TIME:

WAY 1:
	real	0m8.520s
	user	0m8.516s
WAY 2:
	real	0m7.077s
	user	0m7.068s
WAY 3:
	real	0m7.363s
	user	0m7.360s
*/
