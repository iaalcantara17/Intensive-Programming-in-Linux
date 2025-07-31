#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// global scope => shared across all the threads within a process.
long *array, length, nthreads, s;

// creating the thread function
void *scalar(void *id)
{
	long *myid = (long *)id;

	// calculate the chunk for array that each thread would process.
	long chunk = length / nthreads;

	// calculate the start index for each thread
	long start = chunk * (*myid);

	// calculate the end index for each thread
	long end = chunk + start;

	if ((*myid) == nthreads - 1) end = lengthl

	// perform scalar multiplication
	for (int i = start; i < end; i++)
	{
		array[i] *= s;
	}
}

int main(int argc, char **argv)
{
	pthread_t *thread_array;
	
	// parse the command line arguments
	nthreads = strtol(argv[1], NULL, 10);
	length = strtol(argv[2], NULL, 10);
	s = strtol(argv[3], NULL, 10);

	// allocate memory for array, thread_array and thread_ids
	array = (long *)malloc(sizeof(long)*length);
	thread_array = malloc(sizeof(pthread_t)*nthreads);
	thread_ids = (long *)malloc(sizeof(long)*nthreads);

	// initialize the array
	for (int i = 0; i < length; i++)
	{
		array[i] = i;
	}

	// create the threads
	for (int i = 0; i < nthreads; i++)
	{
		thread_ids[i] = i;
		pthread_create(&thread_array[i], NULL, scalar, &thread_ids[i]);
	}

	// join the threads
	for (int i = 0; i < nthreads; i++)
	{
		pthread_join(thread_array[i], NULL);
	}

	// print the array
	for (int i = 0; i < length; i++)
	{
		printf("%ld, ", array[i]);
	}

	free(thread_array);
	free(thread_ids);
	free(array);
	
}
