#include <stdio.h>

int main(int argc, char const *argv[]){
	void *p;

	int a = 1;
	float b = 2.0;
	double c = 3.3;


	//p = &a;
	//printf("%d\n", *p);
	//p = &b;
	//printf("%f\n", *p);
	//p = &c;
	//printf("%lf\n", *p);

	/*output:
	pointer.c:11:17: warning: dereferencing ‘void *’ pointer
	  printf("%d\n", *p);
	                 ^
	pointer.c:11:2: error: invalid use of void expression
	  printf("%d\n", *p);
	  ^
	pointer.c:14:17: warning: dereferencing ‘void *’ pointer
	  printf("%f\n", *p);
	                 ^
	pointer.c:14:2: error: invalid use of void expression
	  printf("%f\n", *p);
	  ^
	pointer.c:17:18: warning: dereferencing ‘void *’ pointer
	  printf("%lf\n", *p);
	                  ^
	pointer.c:17:2: error: invalid use of void expression
	  printf("%lf\n", *p);
	*/

	p = &a;
	printf("%d\n", *((char *) p));

	p = &b;
	printf("%f\n", *(float *) p);

	p = &c;
	printf("%lf\n", *(double *) p);

	return 0;
}