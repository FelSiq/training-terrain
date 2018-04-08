#include <stdio.h>
#include <time.h>

#define OP_NUM 1e+10

int main(int argc, char *argv[]) {
	register unsigned long i;
	register int a=1, b=1, c=0;
	register float d=1.0, e=1.0, f=0.0;
	time_t t;
	// Integer addition
	t = clock();
	for (i = OP_NUM; i--; c = a + b);
	t = clock() - t;
	printf("Time (int addition):\t%lu\taverage: %f\n", t, t/(1.0 * OP_NUM));
	// Integer subtraction
	t = clock();
	for (i = OP_NUM; i--; c = a - b);
	t = clock() - t;
	printf("Time (int subtraction):\t%lu\taverage: %f\n", t, t/(1.0 * OP_NUM));
	// Integer multiplication
	t = clock();
	for (i = OP_NUM; i--; c = a * b);
	t = clock() - t;
	printf("Time (int mult):\t%lu\taverage: %f\n", t, t/(1.0 * OP_NUM));
	// Integer misc
	t = clock();
	for (i = OP_NUM; i--; c = a * b, c = a - b, c = b + a);
	t = clock() - t;
	printf("Time (int misc):\t%lu\taverage: %f\n", t, t/(1.0 * OP_NUM));
	// Floating point addition
	t = clock();
	for (i = OP_NUM; i--; f = d + e);
	t = clock() - t;
	printf("Time (float addition):\t%lu\taverage: %f\n", t, t/(1.0 * OP_NUM));
	// Float subtraction
	t = clock();
	for (i = OP_NUM; i--; f = d - e);
	t = clock() - t;
	printf("Time (float subtr):\t%lu\taverage: %f\n", t, t/(1.0 * OP_NUM));
	// Float multiplication
	t = clock();
	for (i = OP_NUM; i--; f = d * e);
	t = clock() - t;
	printf("Time (float mult):\t%lu\taverage: %f\n", t, t/(1.0 * OP_NUM));
	// Float misc
	t = clock();
	for (i = OP_NUM; i--; f = d * e, f = d - e, f = e + d);
	t = clock() - t;
	printf("Time (float misc):\t%lu\taverage: %f\n", t, t/(1.0 * OP_NUM));

	// This line avoids compiler optimization, as it may detect that the
	// loops above are nearly useless and, if the variables was never used
	// again, it may not run these commands at all.
	printf("%d,%d,%d,%f,%f,%f\n", a, b, c, d, e, f);

	return 0;
}
