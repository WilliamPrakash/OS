#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
	// memory safe way of getting input (puts it on heap, clear heap memory?)
	printf("type a string to be tokenized: ");
	char *buffer;
	size_t bufsize = 32;
	buffer = (char *)malloc(bufsize * sizeof(char));
	getline(&buffer, &bufsize, stdin);
	buffer[strcspn(buffer, "\n")];	// gets rid of newline character

	// Tokenize buffer by char to read it as a char array (string)
	const char s[2] = " ";	// tokenize buffer based on a blank space
	char *token;	// this probably isn't memory safe, stack overflow vulnerability
	token = strtok(buffer, s);
	int i = 0;
	char *arr[20];
	arr[i] = token;

	while(token != NULL){
		token = strtok(NULL, s);
		if(token == NULL){
			break;	// gets rid of segmentation fault error
		}
		//printf("%s", token);
		i++;
		arr[i] = token;
	}

	i = 0;
	// print out contents
	while(i < 20){
		printf("%s ", arr[i]);
		i++;
	}

	// get and store user input in char array
	/*char str[100];
	printf("Enter a value :");
	scanf("%s", str);
	getchar();
	printf("\nYou entered: %s\n", str);*/

	return 0;
}
