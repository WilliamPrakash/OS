#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <time.h>
void timer();
int main(int argc, char *argv[]) {
	// Processes are NOT the same as threads
	// Processes are isolated and do not share emory with any other processes
	// Thread is the segment of a process, which means a process can have multiple threads contained within one process
	// Threads have 3 states: running, ready, blocked
	// Threads do not isolate and share memory
	int processList[10] = {0,0,0,0,0,0,0,0,0,0};

	// spawn initial child process to then create more processes
	printf("\n");
	int child0 = fork();
	int i = 0;
	if(child0 < 0) {
		fprintf(stderr, "fork failed\n");
		exit(1);
	} else if(child0 == 0) {
		// inside childSpawner process (forked process from main)
		int child1 = fork();
		if(child1 == 0) {
			// inside child1 process (forked child from childSpawner)
			char *myargs[2];
			myargs[0] = strdup("./tests/loop1");
			myargs[1] = NULL;
			execvp(myargs[0], myargs);
			exit(0);
		// call timer with parent process of child1 to prevent child1 from always executing
		} else {
			timer(child1);
			wait(NULL);
			//printf("hello from childSpawner, pid: %d\n", (int) getpid());
			exit(0);
		}
	} else {
		// Original parent process, force it to wait for child process
		wait(NULL);
		exit(0);
	}	
}

// parent thread is running concurrently with the thread taken over by child1
// I can have the parent force the child process to stop with this timer
void timer(int pidToKill) {
	printf("pid to kill: %d\n", pidToKill);
	clock_t before, after;
        before = clock();       // this gets the number of clock ticks that have elapsed since the program was launched
        sleep(8);
        after = clock();
        double t1 = ( (double)(after-before) ) / CLOCKS_PER_SEC;
        printf("clock after: %f\n", t1);
	kill(pidToKill, SIGKILL);
}
