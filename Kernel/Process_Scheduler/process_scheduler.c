#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include "system_call_interface.c"

int main(int argc, char *argv[]) {
	int processList[5] = {0,0,0,0,0};

	// this does execute program test1, but it can be done via a process with execvp
	//int status = system("./test1 31 895 04 57");

	/* this should spawn multiple processes */
	// this spawns a child process
	int child = fork();
	int i = 0;
	if(child < 0) {
		fprintf(stderr, "fork failed\n");
		exit(1);
	} else if(child == 0) {
		printf("Child process: %u\n", getpid());
		printf("Parent process: %u\n", getppid());
		processList[i] = (int) getpid();
		i++;		
		
		// now that we're inside a process, use exec to overwrite the forked copy
		access_system_calls(21,"print");

		/*char *myargs[3];
		myargs[0] = strdup("./test1");
		myargs[1] = strdup("32");
		myargs[2] = NULL;
		execvp(myargs[0], myargs);*/
		exit(0);
	} else {
		wait(NULL);
		printf("hello from parent process %d\n", (int) getpid());
	}
	
	


	exit(0);
}


