#include <stdio.h>
#include <math.h>
#include <time.h>

#define LOOP_SIZE 10000
#define REPEAT_TIME 100000

float delay_func(float x) {
	// Just a function to create delay
	// between iterations of the loop
	return sin(x) + tan(x) * cos(x);
}

int main(int argc, char *const agrv[]) {
	
	unsigned long i, j;
	float aux = 0;
	double t_avg = 0; 
	time_t t_aux;
	for (i = 0; i < REPEAT_TIME; i++) {
		t_aux = time(NULL);
		j = LOOP_SIZE;
		while (j > 0) {
			aux += delay_func(0.1);
			--j;
		}
		t_aux = time(NULL) - t_aux;

		t_avg += t_aux / (1.0 * REPEAT_TIME);
	}

	// Just to avoid compiler removing the loops
	// while optimizing
	printf("%f\n", aux);

	printf("Average DEC WHILE loop cost: %lf\n", t_avg);

	return 0;
}
