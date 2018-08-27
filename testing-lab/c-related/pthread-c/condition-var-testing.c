#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <error.h>
#include <errno.h>
#include <sched.h>

#define LIST_SIZE 8
#define TOTAL_TO_PRODUCE 32
#define RELINQUISH_CPU 1

typedef struct {
	unsigned long pack_count;
	pthread_mutex_t mutex;
	pthread_cond_t list_not_full, list_has_items;

	int packages[LIST_SIZE];
	unsigned long list_cur_size;
} arg_struct;

void *f_producer(void *args) {
	arg_struct *arg = (arg_struct *) args;

	const unsigned long packs_to_produce = arg->pack_count;

	unsigned long *list_full_count = malloc(sizeof(unsigned long));
	*list_full_count = 0;

	for (register unsigned long i = 0; i < packs_to_produce; ++i) {
		pthread_mutex_lock(&arg->mutex);
		// Entering critical region
		// Check if list is not full
		while(arg->list_cur_size >= LIST_SIZE) {
			(*list_full_count)++;
			pthread_cond_wait(&arg->list_not_full, &arg->mutex);
		}

		// Produce package here
		arg->packages[arg->list_cur_size++] = 1;
		printf("Produced #%lu package.\n", i);

		// Exiting critical region
		pthread_mutex_unlock(&arg->mutex);

		// Send signal to consumer in order to wake him up,
		// if him is sleeping
		pthread_cond_signal(&arg->list_has_items);

		if (RELINQUISH_CPU)
			sched_yield();
	}

	return (void *) list_full_count;
}

void *f_consumer(void *args) {
	arg_struct *arg = (arg_struct *) args;

	unsigned long *list_empty_count = malloc(sizeof(unsigned long));
	*list_empty_count = 0;

	unsigned long consumed_count = 0;
	while (consumed_count < arg->pack_count) {
		pthread_mutex_lock(&arg->mutex);
		// Now entering critical region

		// Check if list is not empty
		while(arg->list_cur_size <= 0) {
			(*list_empty_count)++;
			pthread_cond_wait(&arg->list_has_items, &arg->mutex);
		}

		// Consume package here
		arg->packages[--arg->list_cur_size] = 0;
		printf("Consumed #%lu package.\n", consumed_count++);

		// Exiting crital region
		pthread_mutex_unlock(&arg->mutex);
		
		// Send signal to producer in order to wake him up,
		// if him is sleeping
		pthread_cond_signal(&arg->list_not_full);

		if (RELINQUISH_CPU)
			sched_yield();
	}

	return (void *) list_empty_count;
}

int main(int argc, char *const argv[]) {
	/*
	Synthesis:
	Condition variables are used to put a thread to sleep whenever
	it needs to a certain condition meet before proceding, without
	unnecessary locking and unlocking mutex variables.

	Important note:
	Condition variables must be created alongside a mutex var.
	Any mutex can have 'n' condition variables associated with it,
	but all condition variables must have one and only one mutex
	corresponding to it.
	*/

	// Create mutex and condition variables
	arg_struct arg = {
		.pack_count = TOTAL_TO_PRODUCE,
		.mutex = PTHREAD_MUTEX_INITIALIZER,
		.list_not_full = PTHREAD_COND_INITIALIZER, 
		.list_has_items = PTHREAD_COND_INITIALIZER,
		.list_cur_size = 0
	};
	for (register unsigned long i = 0; i < LIST_SIZE; ++i) 
		arg.packages[i] = 0;

	// Create threads to test purposes
	pthread_t consumer_id, producer_id;

	pthread_create(&consumer_id, NULL, 
		f_consumer, (void *) &arg);
	pthread_create(&producer_id, NULL, 
		f_producer, (void *) &arg);

	// Join thread just because we are expecting
	// dynamically allocated return values, so
	// they memory blocks must be freed before
	// process ends.
	unsigned long *consumer_ret = NULL, *producer_ret = NULL;
	pthread_join(consumer_id, (void **) &consumer_ret);
	pthread_join(producer_id, (void **) &producer_ret);

	// Check return values
	printf("Consumer checks if lists empty: %lu\n"
		"Producer checks if lists full: %lu\n", 
		*consumer_ret, *producer_ret);

	// Free dynamic memory blocks
	if (consumer_ret)
		free(consumer_ret);
	if (producer_ret)
		free(producer_ret);

	// Statically allocated mutex/condition variables
	// does not need to be destroyed.

	return 0;
}
