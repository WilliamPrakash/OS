#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
	printf("Starting up from original process: %d...\n", (int) getpid());	

	int child = fork();
	if(child < 0){
		printf("fork failed\n");
		exit(1);
	} else if(child == 0) {
		//printf("child process: %d\n", (int) getpid());

		exit(0);
	} else {
		wait(NULL);
		printf("Back in original process: %d\n", (int) getpid());
	}
}
