#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <string.h>
// remember to compile this with the pthread flag

int main(int argv, char *argc[]) {
	char *buffer;
	size_t bufsize = 32;
	buffer = (char *)malloc(bufsize * sizeof(char));
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

	printf("Contents of buffer: ");
	for (i = 0; buffer[i] != '\0'; i++) {
		printf(" %c  ", buffer[i]);
	}
	printf("\n");
	//char *input[10];
	//sscanf(input, "%s", buffer);

	i = 0;
	/*while(buffer[i] != '\n') {
		printf(" %c ", buffer[i]);
		i++;
	}*/
	
	// while loop for interactivity
	if(strcmp(buffer, "ls") == 0) {
		printf("ls command recognized\n");
	}


	return 0;	
}
