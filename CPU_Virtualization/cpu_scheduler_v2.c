#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <time.h>
#include <pthread.h>

void *mutex_test();
void *roll();
void *timer();

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cv;

int main(int argc, char *argv[]) {
	// Processes are NOT the same as threads
	// Processes are isolated and do not share emory with any other processes
	// Thread is the segment of a process, which means a process can have multiple threads contained within one process
	// Threads have 3 states: running, ready, blocked
	// Threads do not isolate and share memory
	
	pthread_t th[2];
	int *res;
	srand(time(NULL));

	for(int i = 0; i < 2; i++) {
		if(pthread_create(th + i, NULL, roll, NULL) != 0){
			perror("Failed to create thread\n");
			return 1;
		}
		printf("Thread %d created\n", i);
	}
	for(int i = 0; i < 2; i++) {
		//if(pthread_join(th[i], NULL) != 0) {
		if(pthread_join(th[i], (void**) &res) != 0) {
                        // pthread_join waits for the thread specified in the first arg to terminate
                        return 1;
                }
		printf("Result: %d\n", *res);
		free(res);
	}
	
	pthread_mutex_destroy(&mutex);
	exit(0);
}

void *mutex_test() {
	// obvious evolution of forever for loop is a queue
	pthread_cond_init(&cv, NULL);
	//while(1) {
		if(pthread_mutex_trylock(&mutex) == 0) {
			pthread_mutex_lock(&mutex);
			printf("mutex has been locked\nPerforming a task for 3 seconds...\n");
			sleep(3);
			pthread_mutex_unlock(&mutex);
			printf("unlocked\n");
			pthread_cond_signal(&cv);
        	} else {
			printf("pausing other thread while waiting for mutex to be unlocked\n");
			pthread_cond_wait(&cv, &mutex); // this will wait for a signal from another thread
			// ^^^ Equivalent to:
			// pthread_mutex_unlock(&mutex)
			// wait for signal on cv
			// pthread_mutex_lock(&mutex)
			printf("other thread has been resumed\n");
        	}
	//}
	pthread_cond_destroy(&cv);
}

void *roll() {
	int value = (rand() % 6) + 1;
	int *result = malloc(sizeof(int));
	*result = value;
	return (void*) result;	// you can't return a reference to a local variable, will be deallocated 
}

void *timer() {
	clock_t before, after;
        before = clock();       // this gets the number of clock ticks that have elapsed since the program was launched
        sleep(8);
        after = clock();
        double t1 = ( (double)(after-before) ) / CLOCKS_PER_SEC;
        printf("clock after: %f\n", t1);
}
