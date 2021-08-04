#include <stdlib.h>
#include <stdio.h>
//#include <pthread.h>	// not even using this... yet
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
//  NOTE: compile this with -lpthread flag
// fork() lets you create and run a copy of the original process
// exec() lets you run a different process in place of the copy of the original process

int main(int argv, char *argc[]) {
	char *buffer;
	size_t bufsize = 32;
	buffer = (char *)malloc(bufsize * sizeof(char));

	while(strcmp(buffer, "exit") != 0) {		
		memset(buffer, 0, sizeof buffer);	// clear buffer before a new command is taken in
		printf("-> ");
        	int i;
	        getline(&buffer, &bufsize, stdin);
        
        	void removeNewLineCharacter(char *ptr){		// removes newline from buffer
                	while( (ptr != NULL) && (*ptr != '\n') ){
                        	++ptr;
	                }
        	        *ptr = '\0';
	        }
	        removeNewLineCharacter(buffer);

        	i = 0;
       		 /*while(buffer[i] != '\n') {
                	printf(" %c ", buffer[i]);
	                i++;
        	}*/

	        if(strcmp(buffer, "ls") == 0) {			
	                printf("ls command recognized\n");
		}
		
		if(strcmp(buffer, "create process") == 0) {
			//printf("Main process pid: %d\n", (int) getpid());
			int child = fork();	// returns an id of 0 to the child process -> different from pid?
			if(child < 0) {
				fprintf(stderr, "fork failed\n");
				exit(1);
			} else if (child == 0) {
				printf("hello from child process number %d\n", (int) getpid());
				//sleep(1);
				//kill(child, SIGTERM);
				exit(0);
			} else {
				//int wc = wait(NULL);
				wait(NULL);
				//kill(child, SIGTERM);
				printf("hello from parent process %d\n", (int) getpid());
			}
		}

	}

	return 0;	
}
