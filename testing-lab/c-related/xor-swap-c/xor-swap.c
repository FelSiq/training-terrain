#include <stdio.h>

int main(int argc, char *const argv[]) {

	int c = 123456, d = 2^20 - 1;
	float a = 1233.231, b = 1.42e+1;
	char e = 'f', f = 'e';
	int *pc = &d, *pd = &c;

	printf("c = %d\nd = %d\n", c, d);
	//c ^= d ^= c; // Buggy Swap! Don't work!!!!!
	c ^= d;
	d ^= c;
	c ^= d;
	printf("c = %d\nd = %d\n", c, d);

	printf("e = %d\nf = %d\n", e, f);
	e ^= f;
	f ^= e;
	e ^= f;
	printf("e = %d\nf = %d\n", e, f);

	printf("pc = %p\npd = %p\n", pc, pd);
	pc = (long int) pc ^ (long int) pd;
	pd = (long int) pd ^ (long int) pc;
	pc = (long int) pc ^ (long int) pd;
	printf("pc = %p\npd = %p\n", pc, pd);

	int x = 5, y = 5;

	printf("x = %d\ny = %d\n", x, y);
	x ^= y;
	y ^= x;
	x ^= y;
	printf("x = %d\ny = %d\n", x, y);
	return 0;
}
