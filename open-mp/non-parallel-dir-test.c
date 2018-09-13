#include <stdio.h>
#include <omp.h>

#define N 5

int main(int argc, char *const argv[]) {

	printf("Dynamic thread num enabled? %d\n", omp_get_dynamic());

	omp_set_num_threads(4);
	printf("Max thread that can be created in a"
		" parallel directive = %d\n", omp_get_max_threads());

	omp_set_nested(1);

	printf("Scheduling strategy: %s\n", OMP_SCHEDULE);

	#pragma omp parallel num_threads(2)
	{
		printf("Outter loop: Thread num in this team = %d\n", omp_get_num_threads());
		int master_id = omp_get_thread_num();
		#pragma omp for
		for (int i = 0; i < N; ++i) {
			printf("outter for : %d\n", omp_get_thread_num());
			
			#pragma omp parallel shared(master_id) num_threads(4)
			{
				printf("Inner loop: Thread num in this team = %d\n", omp_get_num_threads());
				#pragma omp for
				for (int j = 0; j < N; ++j) {
					printf("inner for : (%d, %d)\n", 
						master_id, omp_get_thread_num());
				}
			}
		}
	}
	printf("Master only: Thread num in this team = %d\n", omp_get_num_threads());


	return 0;
}
