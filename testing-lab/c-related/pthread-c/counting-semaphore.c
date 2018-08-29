#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

#define THREAD_NUM 16
#define SEM_VAL 4
#define LOOP_SIZE 32

typedef struct {
	sem_t sem;
	pthread_mutex_t mutex;
	unsigned char t_in_region[THREAD_NUM];
} args_struct;

void *func(void *arg) {
	args_struct *args = (args_struct *) arg;

	register unsigned int i = 0;

	pthread_mutex_lock(&args->mutex);
	while (args->t_in_region[i] != 2) 
		i++;
	args->t_in_region[i] = 0;
	pthread_mutex_unlock(&args->mutex);

	const unsigned short int thread_id = i;

	int sem_val;
	for (i = 0; i < LOOP_SIZE; ++i) {

		// If semaphore > 0, decrement and proceed
		// Sleep otherwise until some thread call sem_post(...).
		sem_wait(&args->sem);
	
		args->t_in_region[thread_id] = 1;

		// Mutex is used just because of printf,
		// to keep interface making sense.
		pthread_mutex_lock(&args->mutex);
		sem_getvalue(&args->sem, &sem_val);
		printf("(%d) Thread %hu\t entered critical region: ",
			SEM_VAL - sem_val, thread_id);

		for (register unsigned int j = 0; j < THREAD_NUM; ++j)
			printf("[%c]", (args->t_in_region[j]==1) ? 'X' : '_');
		printf("\n");
		pthread_mutex_unlock(&args->mutex);
		args->t_in_region[thread_id] = 0;

		// Increment semafore value and wake up threads
		// sleeping due to sem_wait(...).
		sem_post(&args->sem);
	}

	return NULL;
}

int main(int argc, char *argv[]) {
	args_struct args = {.mutex = PTHREAD_MUTEX_INITIALIZER};
	for (unsigned short int i = 0; i < THREAD_NUM; ++i)
		args.t_in_region[i] = 2;

	// The value of the semaphore tells how many
	// processes/threads may enter on the critical
	// region at the same time
	sem_init(&args.sem, 0, SEM_VAL);

	pthread_t threads[THREAD_NUM];

	for (unsigned short int i = 0; i < THREAD_NUM; ++i)
		pthread_create(threads + i, NULL, func, (void *) &args);

	// Joining just because semaphore should be
	// destroyed before process ends.
	for (unsigned short int i = 0; i < THREAD_NUM; ++i)
		pthread_join(threads[i], NULL);

	int sem_count;
	sem_getvalue(&args.sem, &sem_count);
	printf("Final semaphore count: %d\n", sem_count);
	
	sem_destroy(&args.sem);
	return 0;
}
