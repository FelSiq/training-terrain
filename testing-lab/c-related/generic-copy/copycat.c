#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/*
	Code showing how to copy data from a void *
	source to a generic destiny using just the
	size of the source as extern information.
*/

// Way 1
void generic_copy1(void *const dest, void *const src, const size_t size) {
	unsigned char *const aux_a = dest;
	unsigned char *const aux_b = src;

	for (register size_t i = 0; i < size; i++) {
		aux_a[i] = aux_b[i];
	}
}

// Way 2
void generic_copy2(void *const dest, void *const src, const size_t size) {
	register size_t i = 0;
	while (i < size) {
		*(unsigned char *)(dest + i) = *(unsigned char *)(src + i);
		i++;
	}
}

// Way 3
void generic_copy3(void *const dest, void *const src, const size_t size) {
	memcpy(dest, src, size);
}

// SWAP
static void swap(register void *a, register void *b, register size_t size_memb) {
	register unsigned char c;
	while(size_memb--) {
		c = *(unsigned char *)a;
		*(unsigned char *)(a++) = *(unsigned char *)b;
		*(unsigned char *)(b++) = c;
		
		/*
		XOR swaps are worse.
			*(unsigned char *)a ^= *(unsigned char *)b;
			*(unsigned char *)b ^= *(unsigned char *)a;
			*(unsigned char *)a++ ^= *(unsigned char *)b++;
		*/
	}
}

// Testing section
typedef int type_test;
#define printf_mask "dest %d src %d\n"
#define loop_rep (size_t) 1000000000

int main(int argc, char *argv[]) {

	type_test src = ((unsigned) -1) >> 1;
	type_test dest = 1;

	for (register size_t j = 0; j < loop_rep; j++) 
		generic_copy2(&dest, &src, sizeof(type_test));

	printf(printf_mask, dest, src);

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
