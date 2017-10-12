#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

#define HEAP_TEST 0
#define THREAD_NUM 4

#define DEFLOOP for (int i = 0; i < THREAD_NUM; ++i)

void *my_function(void *args) {
	printf("Thread #%d SP value (method 1): %p\n", *(int *)args, __builtin_frame_address(0)); // 0 So we get the address of this function
	// Use 1 to obtain the frame address of the caller
	// font: https://gcc.gnu.org/onlinedocs/gcc-4.8.0/gcc/Return-Address.html
	register int sp asm ("sp");
	printf("Thread #%d SP value (method 2): %x\n", *(int *)args, sp);
	#if HEAP_TEST
		long long int *a = malloc(sizeof(long long int));

		for (int i = 0; i < (1 << (sizeof(int) * 8 - 4)); ++i)
			*a += 2;
		pthread_exit((void *) a);
	#else
		long long int a = 0;

		for (int i = 0; i < (1 << (sizeof(int) * 8 - 4)); ++i)
			a += 2;

		pthread_exit((void *) &a);
	#endif
}

int main(int argc, char const *argv[]) {
	pthread_t *threads = malloc(sizeof(pthread_t) * THREAD_NUM);
	int index[THREAD_NUM];
	long long int retValues[THREAD_NUM];

	if (!threads) {
		printf("An error ocurred at creating the thread vector.\n");
		return 1;
	}

	#if HEAP_TEST
		printf("THIS IS A HEAP TEST!\n");
	#else
		printf("THIS IS A STACK TEST!\n");
	#endif

	// printf("Size of pthread_t: %lu.\n", sizeof(pthread_t));
	// output: 8 bytes

	DEFLOOP {
		index[i] = i;
		pthread_create((i + threads), NULL, my_function, (void *) (index + i));
	}

	DEFLOOP {
		pthread_join(*(i + threads), (void *) (i + retValues));
	}

	DEFLOOP {
		printf("> Thread #%d ret val: %p\n", i, (i + retValues));

		for (int j = 0; j < THREAD_NUM; ++j)
			if (j != i) 
				printf("\t- (%d - %d): %ld\n", i, j, (long int) (*(i + retValues) - *(j + retValues)));
	}

	#if HEAP_TEST
		DEFLOOP {
			free((void *) *(i + retValues));		
		}
	#endif

	free(threads);

	return 0;
}



/*
Conclusions:
	- Thread's Stacks are different and unique.
	- Stack pointers are different (consequence).
	- Stacks address order of different threads are, at first, deterministic 
		(the first thread is in a more "memory-deep" location, alongside the last created one has more proximity with the 0 address)
	- Heap region of different threads are non-deterministic
	- Each thread has a default stack size of its own (8392704 bytes in this machine)
		To be rigorous, this machine has a stack size defined to a maximum of exactly 8388608 bytes
		8392704 - 8388608 = 4096 "non-stack" bytes between each thread. What purpose can these serve?
*/