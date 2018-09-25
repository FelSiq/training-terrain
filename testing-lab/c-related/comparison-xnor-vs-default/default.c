#include <stdio.h>
#include <time.h>

#define REPEAT 100
#define LOOP_SIZE (unsigned long int) 100000000

int main(int argc, char *argv[]) {

	unsigned long long int total_time = 0;
	int a[] = {1, 2, 3}, b[] = {1, 3, 2};
	unsigned char res;

	time_t t;

	for (unsigned long int k = 0; k < REPEAT; k++) {
		t = time(NULL);
		for (unsigned long int i = 0, j = 0; i < LOOP_SIZE; i++) {
			res = (a[j] == b[j]);
			j = (j + 1) % (sizeof(a)/sizeof(int));
		}
		t = time(NULL) - t;
		total_time += t;
	}

	printf("Total time: %llu\nAvrg time: %lf\n", total_time, total_time / (1.0 * REPEAT));

	return 0;
}
