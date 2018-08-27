#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <error.h>
#include <sched.h>
#include <errno.h>

#define LOOP_SIZE 10
#define MUTEX_NUM 3

typedef struct {
	pthread_mutex_t mutex[MUTEX_NUM];
} arg_struct;

/*
	This program uses the 'back-off' tatic to
	prevent deacklocks, which consists of each
	thread unlocking all its owned mutex var-
	iables if a single attempt to lock another
	mutex fails (because it's already owned by
	another thread).
*/

void *t_func_a(void *args) {
	pthread_mutex_t *mutex_list = ((arg_struct *) args)->mutex;

	const long unsigned int thread_id = pthread_self();

	int status = 0;
	for (long j = 0; j < LOOP_SIZE; ++j) {
		for (register long i = 0; i < MUTEX_NUM; ++i) {
			if (i == 0) {
				// First mutex should be locked with _lock(...)
				status = pthread_mutex_lock(mutex_list + i);
			} else {
				// Subsequent ones must be with _trylock(...),
				// which does not block thread in case of fail
				status = pthread_mutex_trylock(mutex_list + i);
			}

			if (status == EBUSY) {
				printf("Thread %lu backing off..\n", thread_id);
				// Back-off: unlock all owned mutex
				for (--i; i >= 0; --i)
					pthread_mutex_unlock(mutex_list + i);
			}
		}

		if (status != EBUSY) {
			printf("Thread %lu owning all mutex!\n", thread_id);
		}

		for (register long i = 0; i < MUTEX_NUM; ++i)
			pthread_mutex_unlock(mutex_list + i);

		// Relinquish CPU
		sched_yield();
	}

	return NULL;
}

void *t_func_b(void *args) {
	pthread_mutex_t *mutex_list = ((arg_struct *) args)->mutex;

	const long unsigned int thread_id = pthread_self();

	int status = 0;
	for (long j = 0; j < LOOP_SIZE; ++j) {
		for (register long i = MUTEX_NUM-1; i >= 0; --i) {
			if (i == 0) {
				// First mutex should be locked with _lock(...)
				status = pthread_mutex_lock(mutex_list + i);
			} else {
				// Subsequent ones must be with _trylock(...),
				// which does not block thread in case of fail
				status = pthread_mutex_trylock(mutex_list + i);
			}

			if (status == EBUSY) {
				printf("Thread %lu backing off..\n", thread_id);
				// Back-off: unlock all owned mutex
				for (++i; i < MUTEX_NUM; ++i)
					pthread_mutex_unlock(mutex_list + i);
			}
		}

		if (status != EBUSY) {
			printf("Thread %lu owning all mutex!\n", thread_id);
		}

		for (register long i = MUTEX_NUM-1; i >= 0; --i)
			pthread_mutex_unlock(mutex_list + i);

		// Relinquish CPU
		sched_yield();
	}

	return NULL;
}

int main(int argc, char *const argv[]) {
	pthread_t a, b;

	arg_struct args;
	for (register long i = 0; i < MUTEX_NUM; ++i)
		pthread_mutex_init(args.mutex + i, NULL);

	pthread_create(&a, NULL, t_func_a, (void *) &args);
	pthread_create(&b, NULL, t_func_b, (void *) &args);

	// Can not detach threads this time because
	// mutex variables must be destroyed after-
	// wards only when both threads that use
	// then ends.
	pthread_join(a, NULL);
	pthread_join(b, NULL);

	for (register long i = 0; i < MUTEX_NUM; ++i)
		pthread_mutex_destroy(args.mutex + i);

	// Using pthread_exit at the process
	// main thread does not ends it, diff-
	// erently from the 'return' statement.
	// pthread_exit(NULL);

	return 0;
}
