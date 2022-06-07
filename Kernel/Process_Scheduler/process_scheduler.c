#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

int main(int argc, char *argv[] ) {
	int processList[10] = {0,0,0,0,0,0,0,0,0,0};
	const int pidMin = 101;

	// this does execute program test1, but it can be done via a process with execvp
	//int status = system("./test1 31 895 04 57");

	// this spawns a child process
	int child = fork();
	int i = 0;
	if(child < 0) {
		fprintf(stderr, "fork failed\n");
		exit(1);
	} else if(child == 0) {
		printf("hello from child process number %d\n", (int) getpid());
		processList[i] = (int) getpid();
		//printf("inside processList v1: %d\n", processList[i]);
		char *myargs[3];
		myargs[0] = strdup("./test1");
		myargs[1] = strdup("32");
		myargs[2] = NULL;
		execvp(myargs[0], myargs);
		exit(0);
	} else {
		wait(NULL);
		printf("hello from parent process %d\n", (int) getpid());
	}
	
	i = 0;
	// after the process is finished running and exits, it no longer appears in here...
	//printf("inside processList v2: %d\n", processList[i]);

	// load process into memory
	// malloc()
	


	//exit(1);
}


