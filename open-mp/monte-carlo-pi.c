#include <stdlib.h>
#include <stdio.h>
#include <omp.h>

/*
	MONTE CARLO method for calculating PI.

	Area_Square = (2*R)^2
	Area_Circle = (pi*R^2)

	Area_Circle/Area_Square = (pi*R^2) / (4*R^2) = pi / 4

	therefore

	4 * Area_Circle/Area_Square = pi

*/

#define INT_MAX (int) (((long) 1 << (sizeof(int) * 8 - 1)) - 1)

#define SQR(X) ((X)*(X))
#define POINTS_NUM (unsigned long int) 1024*1024*8
#define RADIUS 2.0

int main(int argc, char *const argv[]) {
	printf("POINTS_NUM = %lu\n", POINTS_NUM);
	 
	double rand_no_x, rand_no_y;
	unsigned long int i, sum, npoints = POINTS_NUM;
	#pragma omp parallel \
		num_threads(4) \
		private(i, rand_no_x, rand_no_y) shared(npoints) \
		reduction(+: sum)
	{
		sum = 0;
		#pragma omp for
		for (i = 0; i < npoints; i++) {
			rand_no_x = RADIUS * rand()/(1.0 * INT_MAX);
			rand_no_y = RADIUS * rand()/(1.0 * INT_MAX);
			if ((SQR(rand_no_x - RADIUS) + SQR(rand_no_y - RADIUS)) < SQR(RADIUS))
				sum++;
		
		}

	}

	printf("result: %lf\n", 4.0 * sum/(1.0 * POINTS_NUM));
}
