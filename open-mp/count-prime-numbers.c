#include <omp.h>
#include <stdio.h>
#include <math.h>

#define NUM_THREADS 3
#define N 10000000

/*
	Cool link about prime number
	https://primes.utm.edu/howmany.html
*/

int main(int argc, char *const argv[]) {

	register unsigned long int i, j, not_prime_count = 0, 
		odd_i, sqrt_odd_i;

	const register unsigned long total_num = ceil(N/2.0);

	/*
		Some basics to speed up Prime Number countage:

		Number theory tricks:
		- Skip even numbers: the only even prime is 2.
		- Skip even division checking: A even number can only 
			divide another even number. We're skipping even
			numbers, so we can skip even checking, too.
		- We only need to check if a set of numbers 
			C = {1, 2, ..., j} divides i up to j = sqrt(i).
			It is not possible some number n > sqrt(i) to
			divide i, as sqrt(i) is the largest possible
			prime factor of any number i.

		Programming tricks:
		- Don't count the # of prime numbers. Count non-prime 
			numbers. So, you can abuse the break usage.
			The # of prime numbers is = (total - non-prime).
		- Use registers to store indexes and common variables.
		- Don't calculate sqrt(i) inside for loop condition sec-
			tion, otherwise (w/o compiler optimizations) 
			it will recalculate that value every iteration.
		- Use parallel programming to divide the data space.

	*/

	#pragma omp parallel for \
		schedule(dynamic, 10) \
		num_threads(NUM_THREADS) \
		reduction(+: not_prime_count) \
		default(none) \
		private(i, j, odd_i, sqrt_odd_i)
	for (i = 1; i < total_num; i++) {
		odd_i = 2 * i + 1;
		sqrt_odd_i = (unsigned long) sqrt(odd_i);
		for (j = 3; j <= sqrt_odd_i; j += 2) {
			if (odd_i % j == 0) {
				not_prime_count++;
				break;
			}
		}
	}

	printf("%lu\n", N != 1 ? total_num - not_prime_count : 0);

	return 0;
}
