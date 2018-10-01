#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define REPEAT_EXP 10000
#define LOOP_SIZE 1000000

int main(int argc, char *agrv[]) {

	register time_t total_t = 0;
	register unsigned long int i, j;
	register unsigned long int anti_optimization_var = 0;
	register time_t cur_time;

	div_t ans;

	for (i = 0; i < REPEAT_EXP; i++) {

		cur_time = time(NULL);
		for (j = 0; j < LOOP_SIZE; j++) {
			// Let if overflow, it does not matter
			ans = div(j, REPEAT_EXP);
			// Just to use the quo and rem variables outside
			// the loop, to prevent compiler to remote that
			// variable
			anti_optimization_var += (ans.quot - ans.rem) > 0;
		}
		cur_time = time(NULL) - cur_time;	

		total_t += cur_time;

		// Preventing compiler removing loops
		if (anti_optimization_var > REPEAT_EXP)	
			anti_optimization_var /= rand();

	}
	
	printf("Anti_optimization_var: %lu\n", 
		anti_optimization_var);

	printf("Total time: %lu\nAvg time: %lf\n", 
		total_t, total_t / (1.0 * REPEAT_EXP));

	return 0;
}
