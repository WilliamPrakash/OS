#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/wait.h>
#include <sys/types.h>

// refresher:
// int i declares an int
// int* i declares a pointer to an int
// int& r = i declares a reference to an int, and initializes it to refer to i
// pointers are variables that can store addresses and be null

// ISSUES:
// typing in a command that doesn't match any commands won't kill that child process

int main(int argc, char *argv[]){

bool interactive = false;
bool batch = false;
// Shell can be invoked with either a single argument or no argument, anything else, throw an error
if(argc == 1){
	interactive = true;
}
else if (argc == 2){
	batch = true;
}
else {
	printf("Error: shell can only be invoked with 0 or 1 argument(s)\n");
	exit(0);
}


/** Interactive mode **/
if(interactive == true){
char *buffer;
size_t bufsize = 32;

while(1){
	bool executedCommand = false;
	bool runInParallel = false;

	printf("grsh> ");
	buffer = (char *)malloc(bufsize * sizeof(char));
	getline(&buffer, &bufsize, stdin);
	buffer[strcspn(buffer, "\n")] = 0;	// get rid of newline character

	// Tokenize buffer/input by char to read it as a char array (string)
	const char s[2] = " ";
	char *token;
	token = strtok(buffer, s);
	int i = 0;
	char *arr[20];
	arr[i] = token;
	while(token != NULL) {
		token = strtok(NULL, s);
		if(token == NULL){
			break;	// gets rid of segmentation fault error
		}
		i++;
		arr[i] = token;
		if(strcmp(token, "&") == 0){
			runInParallel = true;
		}
	}

	// Built in commands
	int j = 0;
	if(strcmp(arr[j], "exit") == 0){
		exit(0);
	}
	if(strcmp(arr[j], "cd") == 0){
		executedCommand = true;
		chdir(arr[j + 1]);
	}
	// logic for setting path variable
	/*if(strcmp(arr[j], "path") == 0){
	executedCommand = true;
	// while loop to iterate through all variables to add to path
	int k = 1;
		while(k <= i){
			setenv(arr[k], arr[k], 1);
			//printf("Added path variable: %s\n", arr[k]);
			k++;
		}
	}*/

	// Non-parallel child process
	if(executedCommand == false && runInParallel == false){
	executedCommand = true;
	int x = fork();
	if(x < 0){
		printf("fork failed");
	} else if (x == 0) {
		if(strcmp(arr[j], "ls") == 0){
			char *args[2];
			// check if I have access to either of these executables
			//
			int check =  access("/bin/ls",X_OK );
	       		int check1 = access("/usr/bin/ls",X_OK );
			if(check == 0){
				args[0] = "/bin/ls";
			}
			if(check1 == 0){
				args[0] = "/usr/bin/ls";
			}
			args[1] = NULL;
			execv(args[0], args);
		}
		else if(strcmp(arr[j], "cat") == 0){
			// this needs error trapping for when user inputs an incorrect input
			char *args[i+1];
			int check =  access("/bin/cat",X_OK );
			int check1 = access("/usr/bin/cat",X_OK );
	                if(check == 0){
	                	args[0] = "/bin/cat";
	                }
	                if(check1 == 0){
	                	args[0] = "/usr/bin/cat";
	                }
			// while loop to get all arguments from arr
			int k = 1;
			while(k <= i){
				args[k] = arr[k];
				k++;
			}
			args[i+1] = NULL;
			printf("value of i: %d\n", i);
			execv(args[0], args);
			pid_t pid = getpid();
			kill(pid, SIGKILL);
		}
		else if(strcmp(arr[j], "path") == 0){
	       		//executedCommand = true;
	      		// while loop to iterate through all variables to add to path
	       		int k = 1;
	       		while(k <= i){
		       		setenv(arr[k], arr[k], 1);
	               		k++;
	               	}
			pid_t pid = getpid();
			kill(pid, SIGKILL);
	      	}
		else if(strcmp(arr[j], "which") == 0){
	        	//executedCommand = true;
			// concat given file to check with env variable
			char path1[100];
	                strcpy(path1, "/usr/bin/");
	                strcat(path1, arr[j+1]);
	                char path2[100];
	                strcpy(path2, "/bin/");
	         	strcat(path2, arr[j+1]);
	               	if(access(path1, X_OK) == 0){
	                   	printf("%s\n", path1);
	               	}
	               	if(access(path2, X_OK) == 0){
		               	printf("%s\n", path2);
	               	}
			kill(x, SIGKILL);
		}
		else {
			printf("This command doesn't exist");
			pid_t pid = getpid();
			kill(pid, SIGKILL);
		}
	} else {
		// force parent to wait for child
		wait(NULL);
	}}
	/** END of non-parallel child process logic **/

	// Parallel child processes
	if(executedCommand == false && runInParallel == true){
		printf("running in parallel\n");
		}
	}
}
/** End of interactive mode  **/


// Batch mode
/*
if(batch == true){
	FILE *file = fopen(argv[1], "r");
	char *line = NULL;
       size_t buf;
	ssize_t read;
		// Grab one line at a time and perform the commands from that line before going to next line
	while((read = getline(&line, &buf, file)) != -1){
		line[strcspn(line, "\n")] = 0;	// get rid of newline character
		bool executedCommand = false;   // Flag preventing repeated commands
			// Tokenize line
           const char s[2] = " ";
           char *token;
           token = strtok(line, s);
           int i = 0;
           char *arr[20];
           arr[i] = token;
           //printf("First value in arr: %s\n", arr[i]);
           //bool runInParallel = false;
           while(token != NULL) {
               token = strtok(NULL, s);
               if(token == NULL){
                   break;  // gets rid of segmentation fault error
               }
               i++;
               arr[i] = token;
               //printf("added to arr: %s\n", arr[i]);
		}
			// Built in commands
           int j = 0;
           if(strcmp(arr[j], "exit") == 0){
           //if(strcmp(buffer, "exit") == 0){
               exit(0);
           }
           if(strcmp(arr[j], "cd") == 0){
               //printf("Change directory\n");
               executedCommand = true;
               // check if there is more than 1 arg, if so throw error
               //if(i > 2){
               //    printf("Error, too many args");
                //}
               //char x[100];
               chdir(arr[j + 1]);
               //printf("%s\n", getcwd(x, 100)); // print current working directiry
           }
           if(strcmp(arr[j], "path") == 0){
               executedCommand = true;
               // while loop to iterate through all variables to add to path
               int k = 1;
               while(k <= i){
                   setenv(arr[k], arr[k], 1);
                   //printf("Added path variable: %s\n", arr[k]);
                   k++;
               }
           }
            // idk if which should run a whole new process
           if(strcmp(arr[j], "which") == 0){
               executedCommand = true;
               // concat given file to check with env variable
               char path1[100];
               strcpy(path1, "/usr/bin/");
               strcat(path1, arr[j+1]);
               char path2[100];
               strcpy(path2, "/bin/");
               strcat(path2, arr[j+1]);
               if(access(path1, X_OK) == 0){
                   printf("%s\n", path1);
               }
               if(access(path2, X_OK) == 0){
                   printf("%s\n", path2);
               }
           }
		// Non-parallel child process
           if(executedCommand == false){
               //printf("Parent process (pid:%d)\n", (int) getpid());
               executedCommand = true;
               int x = fork();
               if(x < 0){
                   printf("fork failed");
               } else if (x == 0) {
                   // child process
				// ls
                   if(strcmp(arr[j], "ls") == 0){
                       char *args[2];
                       int check =  access("/bin/ls",X_OK );
                       int check1 = access("/usr/bin/ls",X_OK );
                       if(check == 0){
                           args[0] = "/bin/ls";
                       }
                       if(check1 == 0){
                           args[0] = "/usr/bin/ls";
                       }
                       args[1] = NULL;
                       //printf("path: %s\n", args[0]);
                       execv(args[0], args);
                   }
				// cat
                   if(strcmp(arr[j], "cat") == 0){
                       char *args[i+1];
                       int check =  access("/bin/cat",X_OK );
                       int check1 = access("/usr/bin/cat",X_OK );
                       if(check == 0){
                           args[0] = "/bin/cat";
                       }
                       if(check1 == 0){
                           args[0] = "/usr/bin/cat";
                       }
                       //args[1] = "input.txt";
                       // while loop to get all arguments from arr
                       int k = 1;
                       while(k <= i){
                           args[k] = arr[k];
                           k++;
                       }
                       //args[1] = arr[1];
                       args[i+1] = NULL;
                       //printf("contents of arr[1]: %s\n", arr[1]);
                       printf("value of i: %d\n", i);
                       execv(args[0], args);
                   }
                } else {
                   // parent goes down this path
                   wait(NULL);
               }
           }

	}
	fclose(file);
}*/

}
/************************/
/***** END of main  *****/
/************************/


/** Commented out code: **/
/*
// logic for setting path variable
 82                   /*if(strcmp(arr[j], "path") == 0){
 83                              executedCommand = true;
 84                                 // while loop to iterate through all variables to add to path
 85                                 int k = 1;
 86                                 while(k <= i){
 87                                         setenv(arr[k], arr[k], 1);
 88                                         //printf("Added path variable: %s\n", arr[k]);
 89                                         k++;
 90                                 }
 91                         }
 92
 93                         // PUT INSIDE CHILD PROCESS
 94                         /*if(strcmp(arr[j], "which") == 0){
 95                                 executedCommand = true;
 96                                 // concat given file to check with env variable
 97                                 char path1[100];
 98                                 strcpy(path1, "/usr/bin/");
 99                                 strcat(path1, arr[j+1]);
100                                 char path2[100];
101                                 strcpy(path2, "/bin/");
102                                 strcat(path2, arr[j+1]);
103                                 if(access(path1, X_OK) == 0){
104                                         printf("%s\n", path1);
105                                 }
106                                 if(access(path2, X_OK) == 0){
107                                         printf("%s\n", path2);
108                                 }
109                         }

*/
