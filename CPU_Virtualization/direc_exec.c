#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[] ) {
	int processList[10] = {0,0,0,0,0,0,0,0,0,0};
	const int pidMin = 101;

	// create process	->	should this be it's own file?
	int status = system("./test1 31 895 04 57");

	// this spawns a child process
	int child = fork();
	if(child < 0) {
		fprintf(stderr, "fork failed\n");
		exit(1);
	} else if(child == 0) {
		printf("hello from child process number %d\n", (int) getpid());
		exit(0);
	} else {
		wait(NULL);
		printf("hello from parent process %d\n", (int) getpid());
	}

	// load process into memory
	// malloc()
	



}


