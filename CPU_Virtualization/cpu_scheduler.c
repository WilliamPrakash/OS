#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <time.h>
void timer();
int main(int argc, char *argv[]) {
	// TODO: turn processList into a global array that can be manipulated from multiple threads
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
		processList[i] = child0;
		i++;
		int child1 = fork();
		if(child1 == 0) {
			// inside child1 process (forked child from childSpawner)
			char *myargs[2];
			myargs[0] = strdup("./loop1");
			myargs[1] = NULL;
			execvp(myargs[0], myargs);

			exit(0);
		// call timer with parent process of child1 to prevent child1 from always executing
		} else {
			processList[i] = (int) getpid();
			i++;
			timer(child1);
			wait(NULL);
			//printf("hello from childSpawner, pid: %d\n", (int) getpid());
			exit(0);
		}
	} else {
		// Original parent process, force it to wait for child process
		wait(NULL);
		printf("Contents of processList[ ]: \n");
		i = 0;
		printf("%d\n", processList[0]);
		while(processList[i] != 0) {
			printf("%d  ", processList[i]);
			i++;
		}
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
