#include <omp.h>
#include <stdio.h>

#define is_parallel 1

int main(int argc, char *const argv[]) {

	#pragma omp parallel if (is_parallel) \
		num_threads(3) 
	{
		#pragma omp for 
		for (int i = 0; i < 22; ++i)
			printf("%d\n", omp_get_thread_num());

		#pragma omp master
		printf("I'm master thread at master's thread only region.\n"
			"\tI don't have a implicit barrier directive"
			" like single directive does.\n");

		/*

		'Master' directive does not have a implicit
		barrier afterwards.

		*/

		printf("After master reg: %d\n", omp_get_thread_num());

		#pragma omp single
		printf("Hey! I'm thread %d and I entered the single reg!\n", 
			omp_get_thread_num());

		/*

		The 'single' directive places a implicit barrier right here.

		*/

		
		printf("After single reg : %d\n", omp_get_thread_num());
	}

	return 0;
}
