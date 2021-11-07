#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUMTHREADS 2

// Creates a thread-specific data key visible to all threads in the process
// Although the same key value may be used by different threads, the values bound to the key
// by pthread_setspecific() are maintained on a per-thread basis and persist 
// for the life of the calling thread
pthread_key_t glob_var_key;

void do_something()
{
	// get thread specific data
	int* glob_spec_var = pthread_getspecific(glob_var_key);
	printf("Thread %d before mod value is %d\n", (unsigned int) pthread_self(), *glob_spec_var);
	*glob_spec_var += 1;
	printf("Thread %d after mod value is %d\n", (unsigned int) pthread_self(), *glob_spec_var);
}

void* thread_func(void *arg)
{
	// i think malloc has to be used to allocate memory space on the heap
	int *p = malloc(sizeof(int));
	*p = 1;
	// i think this is gonna create two p variables at two different memory addresses, one per thread
	printf("Address of p for thread %d: %p\n", (unsigned int) pthread_self(), p);
	pthread_setspecific(glob_var_key, p);
	do_something();
	do_something();
	pthread_setspecific(glob_var_key, NULL);
	free(p);
	pthread_exit(NULL);
}

int main(void)
{
	pthread_t threads[NUMTHREADS];
	int i;

	pthread_key_create(&glob_var_key,NULL);
	for (i=0; i < NUMTHREADS; i++)
		// each thread will call thread_func, which will make a new pointer variable
		pthread_create(threads+i, NULL, thread_func, NULL);

	for (i=0; i < NUMTHREADS; i++)
		pthread_join(threads[i], NULL);

	return 0;
}

