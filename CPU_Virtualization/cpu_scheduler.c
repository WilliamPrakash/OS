#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

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
			// as soon as execvp() gets executed, loop1 will keep running. It will not relinquish control to this program
			// I can either program a line in there to relinquish it( yield() ), but that's not ideal for all code
			// is there a way I can execute a program from here with a build in lifespan? like somehow execute it for a few seconds?
			
			// not going to reach this code until loop1 is done executing and relinquishes control back to this program
			int stay = 1;
			while(stay = 1){
				kill(child1, SIGSTOP);
				printf("stopped from child1. waiting 3 seconds to continue ./loop1");
				sleep(3);
				kill(child1, SIGCONT);
				printf("loop1 resumed");
				sleep(6);
			}
			exit(0);
		// force childSpawner process to wait for process it created
		} else {
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


