#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <time.h>
#include <pthread.h>

//void *timer();
void *test();
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cv;

int main(int argc, char *argv[]) {
	// Processes are NOT the same as threads
	// Processes are isolated and do not share emory with any other processes
	// Thread is the segment of a process, which means a process can have multiple threads contained within one process
	// Threads have 3 states: running, ready, blocked
	// Threads do not isolate and share memory
	
	pthread_t t1, t2;
	char *message1 = "Thread 1";
	char *message2 = "Thread 2";
	int t1ct, t2ct;

	t1ct = pthread_create(&t1, NULL, test, (void*) message1);
	t2ct = pthread_create(&t2, NULL, test, (void*) message2);

	pthread_join(t1, NULL);
	pthread_join(t2, NULL);

	printf("Thread 1 returns: %d\n", t1ct);
	printf("Thread 2 returns: %d\n", t2ct);
	
	pthread_mutex_destroy(&mutex);
	exit(0);
}

void *test() {
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



/*void *timer() {
	clock_t before, after;
        before = clock();       // this gets the number of clock ticks that have elapsed since the program was launched
        sleep(8);
        after = clock();
        double t1 = ( (double)(after-before) ) / CLOCKS_PER_SEC;
        printf("clock after: %f\n", t1);
}*/
