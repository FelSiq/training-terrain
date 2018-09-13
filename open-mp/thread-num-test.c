#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <omp.h>

#define N (unsigned long) 1024*1024*1024*4

int main(int argc, char *const argv[]) {
	
	double a = 0;

	#pragma omp parallel num_threads(3) \
		reduction(+: a)
	{
		for (unsigned long i = 0; i < N; ++i)
			a += sin(0.5) * cos(1)/2 * 2.0 + 0.001;

		printf("%d\ta = %lf\n", omp_get_thread_num(), a);
	}

	printf("%lf\n", a);


	/*

		Conclusion: num_threads DOES NOT specify the number of
		threads to be created, it does specify the number of
		threads that will participate on the processing within
		the parallel region, and the master thread (ID == 0)
		is one of then.

		In synthesis, when clause num_threads(n) is specified,
		n-1 threads are created.

	*/

	return 0;
}
