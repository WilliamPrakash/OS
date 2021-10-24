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

	/***	make a loop here that iterates through	***/

	pthread_join(t1, NULL);
	pthread_join(t2, NULL);

	printf("Thread 1 returns: %d\n", t1ct);
	printf("Thread 2 returns: %d\n", t2ct);

	exit(0);
}

void *test() {
	// TODO: need to find a way to suspend/resume a thread without the use of sleep and a loop -> pause() ?
	// ^^^ also going to need a way to force an unlock
	// obvious evolution of forever for loop is a queue
	int i = 0;
	while(1) {
		// need to conditionally lock this I think
		// then use pthread_mutex_trylock
		pthread_mutex_lock(&mutex);
		printf("locked\n");
		int j = 0;
		while(1){
			if(j >= 2) {break;}
			sleep(2);
			j++;
		}
		pthread_mutex_unlock(&mutex);
		printf("unlocked\n");
		i++;
		if(i >= 2) { break; };
	}
}





/*void *timer() {
	clock_t before, after;
        before = clock();       // this gets the number of clock ticks that have elapsed since the program was launched
        sleep(8);
        after = clock();
        double t1 = ( (double)(after-before) ) / CLOCKS_PER_SEC;
        printf("clock after: %f\n", t1);
}*/
