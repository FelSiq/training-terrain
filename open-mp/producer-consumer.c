#include <stdlib.h>
#include <stdio.h>
#include <sched.h>

#define LIST_SIZE 5
#define PRODUCE_NUMBER 15

int main(int argc, char *const argv[]) {
	int task, count = PRODUCE_NUMBER;
	int list[LIST_SIZE]; 
	int list_cur_size = 0;

	#pragma omp parallel sections \
		private(task) \
		shared(list_cur_size, list) \
		firstprivate(count)
	{
		#pragma omp section
		{
			while (count) {
				// Producer thread
				#pragma omp critical
				{
					if (list_cur_size < LIST_SIZE) {
						task = count;
						list[list_cur_size++] = task;
						count--;
						printf("[%d]\tProduced: %u\n", list_cur_size, count);
					}
				}
			}
		}

		#pragma omp section
		{
			while (count) {
				// Consumer thread
				#pragma omp critical
				{
					if (list_cur_size > 0) {
						task = list[--list_cur_size];
						count--;

						printf("[%d]\tConsumed: %u\n", list_cur_size, task);
					}
				}
			}
		}
	}

	return 0;
}
