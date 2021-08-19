#include <stdlib.h>
#include <stdio.h>
//#include <pthread.h>	// compile with: '-lpthread' when you start using pthread library
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <dirent.h>

int main(int argv, char *argc[]) {
	char *buffer;
	size_t bufsize = 32;
	buffer = (char *)malloc(bufsize * sizeof(char));

	while(strcmp(buffer, "exit") != 0) {		
		memset(buffer, 0, sizeof buffer);	// clear buffer before a new command is taken in
		printf("-> ");
        	int i;
	        getline(&buffer, &bufsize, stdin);
        
        	void removeNewLineCharacter(char *ptr){
                	while( (ptr != NULL) && (*ptr != '\n') ){
                        	++ptr;
	                }
        	        *ptr = '\0';
	        }
	        removeNewLineCharacter(buffer);

        	i = 0;
	        if(strcmp(buffer, "ls") == 0) {
	        	DIR *dir;	// represents a directory stream (high-level interface)
			struct dirent *file; // struct is like an array, but can hold multiple different data types
			dir = opendir(".");
			while((file = readdir(dir)) != NULL) {
				printf(" %s  ", file->d_name);	// an arrow operator in c allows access to elements in structures and unions
				// it's used with a pointer variable pointing to a structure or union
			}
			printf("\n");
			closedir(dir);
		}

		if(strcmp(buffer, "create process") == 0) {
			int child = fork();
			if(child < 0) {
				fprintf(stderr, "fork failed\n");
				exit(1);
			} else if (child == 0) {
				printf("hello from child process number %d\n", (int) getpid());
				exit(0);
			} else {
				wait(NULL);
				printf("hello from parent process %d\n", (int) getpid());
			}
		}

	}

	return 0;	
}
