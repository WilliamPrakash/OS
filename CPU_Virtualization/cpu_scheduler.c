#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <time.h>
void timer();
int main(int argc, char *argv[]) {
	int processList[10] = {0,0,0,0,0,0,0,0,0,0};

	// spawn initial child process to then create more processes
	printf("\n");
	int childSpawner = fork();	// after this call, you have two processes executing this same code (i think)
	int i = 0;
	if(childSpawner < 0) {
		fprintf(stderr, "fork failed\n");
		exit(1);
	} else if(childSpawner == 0) {
		// inside childSpawner process (forked process from main)
		int child1 = fork();
		if(child1 == 0) {
			// inside child1 process (forked child from childSpawner)
			char *myargs[2];
			myargs[0] = strdup("./loop1");
			myargs[1] = NULL;
			execvp(myargs[0], myargs);

			exit(0);
		// force childSpawner process to wait for process it created
		} else {
			timer(child1);
			wait(NULL);
			printf("hello from childSpawner, pid: %d\n", (int) getpid());
			exit(0);
		}

		//exit(0);	// nothing is actually happening with this call! i get the same results with this commented and uncom
	} else {
		// parent process, force it to wait for child process
		wait(NULL);
		printf("hello from parent process %d\n", (int) getpid());
		exit(0);
	}	

	//exit(1);
}

// parent thread is running concurrently with the thread taken over by child1
// I can have the parent force the child process to stop with this timer
void timer(int pidToKill) {
	printf("pid to kill: %d", pidToKill);
	clock_t before, after;
        before = clock();       // this gets the number of clock ticks that have elapsed since the program was launched
        //printf("clock before: %f\n", t);
        sleep(8);
        after = clock();
        double t1 = ( (double)(after-before) ) / CLOCKS_PER_SEC;
        printf("clock after: %f\n", t1);
	kill(pidToKill, SIGKILL);
}
