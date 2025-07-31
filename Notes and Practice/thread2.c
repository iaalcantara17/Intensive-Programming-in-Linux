#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *helloWorld(void *id)
{
	long *myid = (long *)id;
	printf("I'm a thread %ld \n", *myid);
	return NULL;
}

int main(int argc, char **argv)
{
	long nthreads; // number of threads
	pthread_t * thread_array; // array of threads
	long *thread_ids;
	
	nthreads = strtol(argv[1], NULL, 10);

	// allocate memory
	thread_array = malloc(sizeof(pthread_t) * nthreads);
	thread_ids = (long *)malloc(sizeof(long) * nthreads);

	// create threads
	for (int i = 0; i < nthreads; i++)
	{
		thread_ids[i] = i;
		pthread_create(&thread_array[i], NULL, helloWorld, &thread_ids[i]);
	}

	// join the threads
	for (int i = 0; i < nthreads; i++)
	{
		pthread_join(thread_array[i], NULL);
	}
}
