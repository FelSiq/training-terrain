#include <stdlib.h>
#include <stdio.h>
#include <omp.h>

#define N 16
#define M 10000

int main(int argc, char *const argv[]) {
	#pragma omp parallel for schedule(static, 1) num_threads(4)
	for (int i = 0; i < N; ++i)
		printf("%d\t%d\t%d\n", omp_get_thread_num(), 
			i, (i % omp_get_num_threads()) == omp_get_thread_num());

	/*

	The static scheduling uses a round-robin distribution strategy.

	*/

	#pragma omp parallel for schedule(dynamic, 1) num_threads(4)
	for (int i = 0; i < N; ++i)
		printf("%d\t%d\t\n", omp_get_thread_num(), i);

	int freq[32] = {0};
	#pragma omp parallel num_threads(8)
	{
		#pragma omp for schedule(guided, 10)
		for (int i = 0; i < M; ++i)
			freq[omp_get_thread_num()]++;
	}
	for (int i = 0; i < 32; ++i)
		printf("%d ", freq[i]);
	printf("\n");

	#pragma omp parallel for schedule(runtime) num_threads(4)
	for (int i = 0; i < N; ++i)
		printf("%d\t%d\t%d\n", omp_get_thread_num(), 
			i, (i % omp_get_num_threads()) == omp_get_thread_num());

	return 0;

}
