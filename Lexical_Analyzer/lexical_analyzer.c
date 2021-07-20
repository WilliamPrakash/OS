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
	// gets rid of newline character
	void removeNewLineCharacter(char *ptr){
		while( (ptr != NULL) && (*ptr != '\n') ){
			++ptr;
		}
		*ptr = '\0';
	}
	removeNewLineCharacter(buffer);

	// Initialize array to hold tokenized buffer
	const char s[2] = " ";	// tokenize buffer based on a blank space
	char *token;	// this probably isn't memory safe, stack overflow vulnerability
	token = strtok(buffer, s);
	int i = 0;
	char *arr[20];
	arr[i] = token;
	int arrCount = 0;

	// Tokenize buffer after assigning the first element to arr[0]
	while(token != NULL){
		token = strtok(NULL, s);
		if(token == NULL){
			break;	// gets rid of segmentation fault error
		}
		arrCount++;
		i++;
		arr[i] = token;
	}

	// counts for different types of tokens???
	
	// IDEA: add brackets to a stack data structure to ensure equal opening/closing brackets

	//i = 0;
	// Parse through array
	while(i < 20){
		if(arr[i] == NULL){
			break;
		}
		if( (strcmp(arr[i], "(") == 0)) { 
			printf("Memory address of %s: %p\n", arr[i], &arr[i]);
			printf("It works\n");
		}
		i++;
	}

	return 0;
}
