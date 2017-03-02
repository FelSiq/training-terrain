#include <stdio.h>

/*
void finalFunc(int a, int b, int c, int f, int g, int h, int i, int j, int l){
	int k;
	printf("<FFUNC> K LOCAL adress: %p\n", &k);
	printf("A param adress: %p\t (K - a) : %ld\n", &a, &k - (int *) &a);
	printf("B param adress: %p\t (K - b) : %ld\n", &b, &k - (int *) &b);
	printf("C param adress: %p\t (K - c) : %ld\n", &c, &k - (int *) &c);
	printf("F param adress: %p\t (K - f) : %ld\n", &f, &k - (int *) &f);
	printf("G param adress: %p\t (K - g) : %ld\n", &g, &k - (int *) &g);
	printf("H param adress: %p\t (K - h) : %ld\n", &h, &k - (int *) &h);
	printf("I param adress: %p\t (K - i) : %ld\n", &i, &k - (int *) &i);
	printf("J param adress: %p\t (K - j) : %ld\n", &j, &k - (int *) &j);
	printf("L param adress: %p\t (K - l) : %ld\n", &j, &k - (int *) &l);

	//Apparently, when a VALUE is passed on a parameter to a function, the first
	//SIX ones are stored BEFORE the local variables. The other ones are stored AFTER locals.
	//This happens because (examined the assembly code on test #4), the six first parameters
	//Are actually stored on REGISTERS¹.
	//	A param adress: 0x7fff539ae24c	 (K - a) : 2
	//	B param adress: 0x7fff539ae248	 (K - b) : 3
	//	C param adress: 0x7fff539ae244	 (K - c) : 4
	//	F param adress: 0x7fff539ae240	 (K - f) : 5
	//	G param adress: 0x7fff539ae23c	 (K - g) : 6
	//	H param adress: 0x7fff539ae238	 (K - h) : 7
	//	I param adress: 0x7fff539ae270	 (K - i) : -7
	//	J param adress: 0x7fff539ae278	 (K - j) : -9
	//	L param adress: 0x7fff539ae278	 (K - l) : -11




	¹:
	pushq	$135 		< 8th
	pushq	$134 		< 7th
	movl	$133, %r9d 	< 6th
	movl	$132, %r8d 	< 5th
	movl	$131, %ecx 	< 4th
	movl	$130, %edx 	< 3rd
	movl	$129, %esi 	< 2nd
	movl	$128, %edi 	< 1st
}
*/

//Those variables comes BEFORE, on STACK, of variables of all other functions, due to call sequence.
void finalFunc(int *a, int *b, int *c, int *d, int *e, int *f, int *g, int *h, int *i, int *j, int *l,
	int *m, int *n, int *o, int *p, int *q, int *r){
	int k;
	//In previous function, a, b, c, and f was BEFORE, on STACK, in relation of local K.
	//g, h and i comes AFTER.
	printf("<FFUNC> K LOCAL adress: %p\n", &k);
	//ALL NEGATIVE RESULTS (just to corroborate the previous test result)
	//printf("\tK - a: %ld\n\tK - f: %ld\n\tK - i: %ld\n", &k - a, &k - f, &k - i);

	printf("A param adress: %p\t (K - a) : %ld\n", &a, &k - (int *) &a);
	printf("B param adress: %p\t (K - b) : %ld\n", &b, &k - (int *) &b);
	printf("C param adress: %p\t (K - c) : %ld\n", &c, &k - (int *) &c);
	printf("D param adress: %p\t (K - d) : %ld\n", &d, &k - (int *) &d);
	printf("E param adress: %p\t (K - e) : %ld\n", &e, &k - (int *) &e);
	printf("F param adress: %p\t (K - f) : %ld\n", &f, &k - (int *) &f);
	printf("G param adress: %p\t (K - g) : %ld\n", &g, &k - (int *) &g);
	printf("H param adress: %p\t (K - h) : %ld\n", &h, &k - (int *) &h);
	printf("I param adress: %p\t (K - i) : %ld\n", &i, &k - (int *) &i);
	printf("J param adress: %p\t (K - j) : %ld\n", &j, &k - (int *) &j);
	printf("L param adress: %p\t (K - l) : %ld\n", &l, &k - (int *) &l);
	printf("M param adress: %p\t (K - m) : %ld\n", &m, &k - (int *) &m);
	printf("N param adress: %p\t (K - n) : %ld\n", &n, &k - (int *) &n);
	printf("O param adress: %p\t (K - o) : %ld\n", &o, &k - (int *) &o);
	printf("P param adress: %p\t (K - p) : %ld\n", &p, &k - (int *) &p);
	printf("Q param adress: %p\t (K - q) : %ld\n", &q, &k - (int *) &q);
	printf("R param adress: %p\t (K - r) : %ld\n", &r, &k - (int *) &r);

	//Pointers does not seens to obey the rule of "six parameters", tho.
	// A param adress: 0x7ffe7bf01d18	 (K - a) : 3
	// B param adress: 0x7ffe7bf01d10	 (K - b) : 5
	// C param adress: 0x7ffe7bf01d08	 (K - c) : 7
	// D param adress: 0x7ffe7bf01d00	 (K - d) : 9
	// E param adress: 0x7ffe7bf01cf8	 (K - e) : 11
	// F param adress: 0x7ffe7bf01cf0	 (K - f) : 13
	// G param adress: 0x7ffe7bf01ce8	 (K - g) : 15
	// H param adress: 0x7ffe7bf01ce0	 (K - h) : 17
	// I param adress: 0x7ffe7bf01cd8	 (K - i) : 19
	// J param adress: 0x7ffe7bf01cd0	 (K - j) : 21
	// L param adress: 0x7ffe7bf01cc8	 (K - l) : 23
	// M param adress: 0x7ffe7bf01cc0	 (K - m) : 25
	// N param adress: 0x7ffe7bf01cb8	 (K - n) : 27
	// O param adress: 0x7ffe7bf01cb0	 (K - o) : 29
	// P param adress: 0x7ffe7bf01ca8	 (K - p) : 31
	// Q param adress: 0x7ffe7bf01ca0	 (K - q) : 33
	// R param adress: 0x7ffe7bf01c98	 (K - r) : 35
}


void genericFunc(int a, int b, int c, int d, int e, int f, int g, int h, int i, int j,
	int l, int m, int n, int o, int p, int q, int r){
	int k;
	//From a to f, the parameters are stored BEFORE local k variable,
	//with a distance of four bytes (a integer) between two adjascent parameters.
	printf("<GFUNC> K LOCAL adress: %p\n", &k);
	printf("A param adress: %p\t (K - a) : %ld\n", &a, &k - &a);
	printf("B param adress: %p\t (K - b) : %ld\n", &b, &k - &b);
	printf("C param adress: %p\t (K - c) : %ld\n", &c, &k - &c);
	printf("D param adress: %p\t (K - d) : %ld\n", &d, &k - &d);
	printf("E param adress: %p\t (K - e) : %ld\n", &e, &k - &e);
	printf("F param adress: %p\t (K - f) : %ld\n", &f, &k - &f);
	//All parameters below are stored AFTER local variables
	//Interesting: theres TWO integers (8 bytes) of difference between a pair
	//of adjascent parameters
	printf("G param adress: %p\t (K - g) : %ld\n", &g, &k - &g);
	printf("H param adress: %p\t (K - h) : %ld\n", &h, &k - &h);
	printf("I param adress: %p\t (K - i) : %ld\n", &i, &k - &i);
	printf("J param adress: %p\t (K - j) : %ld\n", &j, &k - &j);
	printf("L param adress: %p\t (K - l) : %ld\n", &j, &k - &l);
	printf("M param adress: %p\t (K - m) : %ld\n", &j, &k - &m);
	printf("N param adress: %p\t (K - n) : %ld\n", &j, &k - &n);
	printf("O param adress: %p\t (K - o) : %ld\n", &j, &k - &o);
	printf("P param adress: %p\t (K - p) : %ld\n", &j, &k - &p);
	printf("Q param adress: %p\t (K - q) : %ld\n", &j, &k - &q);
	printf("R param adress: %p\t (K - r) : %ld\n", &j, &k - &r);

	//finalFunc(a, b, c, f, g, h, i, j, l);
	finalFunc(&a, &b, &c, &d, &e, &f, &g, &h, &i, &j, &l, &m, &n, &o, &p, &q, &r);

/*

	K LOCAL adress: 0x7ffed3dc4f04
	A param adress: 0x7ffed3dc4efc	 (K - a) : 2
	B param adress: 0x7ffed3dc4ef8	 (K - b) : 3
	C param adress: 0x7ffed3dc4ef4	 (K - c) : 4
	D param adress: 0x7ffed3dc4ef0	 (K - d) : 5
	E param adress: 0x7ffed3dc4eec	 (K - e) : 6
	F param adress: 0x7ffed3dc4ee8	 (K - f) : 7
	G param adress: 0x7ffed3dc4f20	 (K - g) : -7
	H param adress: 0x7ffed3dc4f28	 (K - h) : -9
	I param adress: 0x7ffed3dc4f30	 (K - i) : -11
	J param adress: 0x7ffed3dc4f38	 (K - j) : -13
	L param adress: 0x7ffed3dc4f38	 (K - l) : -15
	M param adress: 0x7ffed3dc4f38	 (K - m) : -17
	N param adress: 0x7ffed3dc4f38	 (K - n) : -19
	O param adress: 0x7ffed3dc4f38	 (K - o) : -21
	P param adress: 0x7ffed3dc4f38	 (K - p) : -23
	Q param adress: 0x7ffed3dc4f38	 (K - q) : -25
	R param adress: 0x7ffed3dc4f38	 (K - r) : -27

*/

};

int main(int argc, char const *argv[]){
	genericFunc(4, 2, 3, 4, 1, 2, 3, 4, 4, 3, 0, 0, 0, 0, 1, 0, 0);

	//Extra footage:
	//argc is aprox. 240~250 bytes ABOVE argv, on STACK, with a EMPTY main
	//printf("\targc - argv: %ld\n", (void *) &argc - (void *) argv);

	return 0;
};