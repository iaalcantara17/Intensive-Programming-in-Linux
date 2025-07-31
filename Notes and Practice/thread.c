#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
// posix thread

void *computation(void *id);  // always has to be a void pointer for threads
int main()
{
	// declare worker thread
	pthread_t thread1;
	pthread_t thread2;

	long value1 = 1;
	long value2 = 2;
        
	// creating worker threads
	// pthread_create(pthread_t *thread, void *attrs, *thread_func, void *attrs);
	pthread_create(&thread1, NULL, computation, (void *)&value1);
	pthread_create(&thread2, NULL, computation, (void *)&value2);

	// join the threads.
	

	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);
	
}

void *computation(void *id)
{
	int sum;
	long *myid = (long *)id;
	for(int i = 0; i < 1000000000; i++)
	{
		sum += *myid;
	}

	return NULL;
}
