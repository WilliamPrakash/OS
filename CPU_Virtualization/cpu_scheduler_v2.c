#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <time.h>
#include <pthread.h>

void *timer();

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

	t1ct = pthread_create(&t1, NULL, timer, (void*) message1);
	t2ct = pthread_create(&t2, NULL, timer, (void*) message2);

	pthread_join(t1, NULL);
	pthread_join(t2, NULL);

	printf("Thread 1 returns: %d\n", t1ct);
	printf("Thread 2 returns: %d\n", t2ct);

	exit(0);
}



void *timer() {
	clock_t before, after;
        before = clock();       // this gets the number of clock ticks that have elapsed since the program was launched
        sleep(8);
        after = clock();
        double t1 = ( (double)(after-before) ) / CLOCKS_PER_SEC;
        printf("clock after: %f\n", t1);
}
