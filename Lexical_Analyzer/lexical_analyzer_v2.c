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
	
	// Check to make sure more than one string has been inputted to be tokenized -> fixes segmentation fault error
	/*
	int spaceCount = 0;
	void checkForSpace(char *ptr){
		while((ptr != NULL) && (*ptr != '\n')){
			if(*ptr == ' '){	// dereferences pointer ptr (get value at ptr)
				spaceCount += 1;
				break;	// just need to ensure at least one space is there, actual amount doesn't matter
			}
			ptr++;
		}
	}
	checkForSpace(buffer);
	
	if(spaceCount <= 0){
		printf("You need more than one string to tokenize\n");
		return 1;
	}
	*/
	
	// Initialize array to hold tokenized buffer
	/*
	const char s[2] = " ";	// tokenize buffer by space
	char *token;	// stack overflow vulnerability???
	token = strtok(buffer, s);
        int i = 0;
        char *arr[20];
        arr[i] = token;
        int arrCount = 0;
	i = 0;
	*/

	// tokenizing v2 -> iterate through every single thing
	
	// TODO: need to find a way to get all the characters in buffer, cause this shit isn't working

	int i = 0;
	char *token;
	const char s[2] = "";	// I don't this is working;
	token = strtok(buffer, s);
	char *arr[20];
	arr[i] = token;
	//arr[i] = *buffer[i];
	while(token != NULL ) {
		token = strtok(NULL, s);
		if(token == NULL) { break;  };
		i++;
		arr[i] = token;
	}
	// this is only printing . a, I think there is an issue with the tokenizing while loop above
	i = 0;
	int ct = 0;
	printf("All characters in arr: \n");
	while(arr[i] != NULL){
		//if( (arr[i + ct] == "") ) { break;  }; 
		//printf(".  %c  ", *arr[i + ct]);
		printf(". %c ", *arr[i]);
		//++ct;
		i++;
	}
	printf("\n");

	// need a way to tokenize not just based on space, that wouldn't account for this: if(statement){    -> it would get treated as one
	// maybe add every single individual char to array, then tokenize
	// it would iterate over each array element, if it was a number, it would keep going until it hit a non number
	// it would add the number ^^^ as it's own whole string to an array

	/*
	i = 0;
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

	// IDEA: initialize char arrays for all different types of tokens
	// I'll need a way to tell the order of tokens going forward to make a compiler
	char leftBrackets[10];
	int leftBracCount = 0;
	char rightBrackets[10];
	int rightBracCount = 0;
	char operators[10];
	int opCt = 0;
	i = 0;
	// Parse through array
	while(i < 10){
		if(arr[i] == NULL){
			break;
		}
		if( (strcmp(arr[i], "(") == 0) || (strcmp(arr[i], "[") == 0) || (strcmp(arr[i], "{") == 0) ) {
			leftBrackets[leftBracCount] = *arr[i];
			leftBracCount++;
		} else if ( (strcmp(arr[i], ")") == 0) || (strcmp(arr[i], "]") == 0) || (strcmp(arr[i], "}") == 0) ) {
			rightBrackets[rightBracCount] = *arr[i];
			rightBracCount++;
		} else if( (strcmp(arr[i], "+") == 0 )|| (strcmp(arr[i], "-") == 0) || (strcmp(arr[i], "*") == 0) || (strcmp(arr[i], "/") == 0)  ) {
			operators[opCt] = *arr[i];
			opCt++;
		} else{}
		i++;
	}

	// print contents of right and left bracket char arrays
	if(leftBracCount != rightBracCount){
		printf("Inequal amount of left and right brackets\n");
	} else {
		i = 0;
		while(i < leftBracCount){
			printf("LB:  %c\n", leftBrackets[i]);
			printf("RB: %c\n", rightBrackets[i]);
			i++;
		}
	}
	i = 0;
	printf("Operators passed: ");
	while(i < opCt){
		printf("%c ",operators[i] );
		i++;
	}

	*/

	printf("\n");
	return 0;
}
