#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <error.h>
#include <unistd.h>

#define THREAD_NUM 8
#define MAT_DIM 8

typedef struct {
	long int row;
	int (*mat_a)[MAT_DIM];
	int (*mat_b)[MAT_DIM];
	int (*mat_r)[MAT_DIM];
} thread_arg;

void *t_function(void *args) {
	thread_arg *values = (thread_arg *) args;
	int *ret = malloc(sizeof(int));

	// Single row of a matrix multiplication
	const long int row = values->row;
	for (unsigned int i = 0; i < MAT_DIM; i++) {
		int *r_pos = &values->mat_r[row][i];
		*r_pos = 0;

		for (unsigned int j = 0; j < MAT_DIM; ++j)
			*r_pos += values->mat_a[row][j] * values->mat_b[j][i];
	}

	// Just to test return recovery with pthread_join
	*ret = row;
	// Two ways of exiting a thread:
	// Calling return statement, which implicit calls
	// "pthread_exit(ret)". 
	return (void *) ret;

	// Calling pthread_exit(ret) explicit
	// pthread_exit((void *) ret);
	// Note: valgrind accuses memory leak from this method
}

void fill_matrix(int (*m)[MAT_DIM]) {
	for (long i = 0; i < MAT_DIM; ++i)
		for (register long j = 0; j < MAT_DIM; ++j)
			m[i][j] = 1 + i + j;
}

int main(int argc, char *const argv[]) {
	// System max number of threads per process
	long int max_thread_num = sysconf(_SC_THREAD_THREADS_MAX);
	printf("Max thread per process in "
		"this system: %ld\n", max_thread_num);

	// Just a toy data to test pthread,
	// kinda following the example of figure 6.1 in 
	// "Parallel Programming for Multicore and Clusters"
	// by Rauber and Rünger.
	int mat_a[MAT_DIM][MAT_DIM];
	int mat_b[MAT_DIM][MAT_DIM];
	int mat_r[MAT_DIM][MAT_DIM];
	fill_matrix(mat_a);
	fill_matrix(mat_b);

	// Thread-related stuff
	pthread_t t_ids[THREAD_NUM];
	
	// Every thread will have a different argument structure
	thread_arg *t_args[THREAD_NUM];

	// Init threads
	for (register unsigned int i = 0; i < THREAD_NUM; ++i) {
		// Note: can define thread attributes
		// check https://users.cs.cf.ac.uk/Dave.Marshall/C/node30.html
		// for more information

		// Define thread function arguments
		t_args[i] = malloc(sizeof(thread_arg));
		t_args[i]->mat_a = mat_a;
		t_args[i]->mat_b = mat_b;
		t_args[i]->mat_r = mat_r;
		t_args[i]->row = i;
		
		// Init a new joinable thread
		pthread_create(t_ids + i, NULL, t_function, (void *) t_args[i]);
	}

	// Joining threads
	int **ret = malloc(sizeof(int *) * THREAD_NUM);
	for (register unsigned int i = 0; i < THREAD_NUM; ++i) {
		pthread_join(t_ids[i], (void **) ret + i);
	}

	// Print result
	printf("Result:\n");
	for (unsigned int i = 0; i < THREAD_NUM; ++i) {
		printf("thread %d:\t", *ret[i]);
		for (unsigned int j = 0; j < THREAD_NUM; ++j)
			printf("%d\t", mat_r[i][j]);
		printf("\n");
	}
	

	// Note: threads that don't have a "join" call
	// must be detached in order to prevent memory
	// usage from keeping it's inner control struct,
	// which, after thread exiting, is util only if
	// this thread is joined by another one in order
	// to recover it's return value or due to synchro-
	// nization related issues.

	// Freeing dynamic memory
	for (register unsigned int i = 0; i < THREAD_NUM; ++i) {
		free(t_args[i]);
		free(ret[i]);
	}
	free(ret);

	return 0;
}
