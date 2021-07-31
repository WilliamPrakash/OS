#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>

int main(int argc, char *argv[]) {
	// memory safe way of getting input (puts it on heap, clear heap memory?)
	printf("type a string to be tokenized: ");
	char *buffer;
	size_t bufsize = 32;
	buffer = (char *)malloc(bufsize * sizeof(char));
	getline(&buffer, &bufsize, stdin);
	int i = 0;
	int bufCt = 0;
	// iterate through buffer
	printf("Contents of buffer: ");
	for (i = 0; buffer[i] != '\0'; i++){
		printf(" %c  ", buffer[i]);
		bufCt++;
	}
	printf("\n");

	// arrays for holding ints and letters
	char *temp;
	size_t tempSize = 32;
	temp = (char *)malloc(tempSize * sizeof(char));
	int *numbers;
	size_t numbersSize = 32;
	numbers = (int *)malloc(numbersSize * sizeof(int));
	char *strings;
	size_t stringsSize = 100;
	strings = (char *)malloc(stringsSize * sizeof(char));
	//int k = 0;
	int numCt = 0;
	int strCt = 0;	// this isn't actually a string count, it's a char count
	int num;
	// iterate through buffer, parsing ints, strings, brackets
	for(i = 0; i < bufCt; i++) {
		// Grabs all numbers
		if(isdigit(buffer[i])) {
			int j = 0;
			while(isdigit(buffer[i])) {
				temp[j] = buffer[i];
				i++;
				j++;
			}
			i--;	// this is necessary cause the for loop increments i, this prevents numbers from being skipped
			// convert temp to an int and add it to numbers array
			sscanf(temp, "%d", &num);
			numbers[numCt] = num;
			memset(temp, 0, sizeof temp);
			numCt++;
		}
		// Grabs all 'strings'
		else if(isalpha(buffer[i])) {
			int j = 0;
			while(isalpha(buffer[i])) {
				temp[j] = buffer[i];
				i++;
				j++;
			}
			i--;
			// loop through temp to add the characters to strings char array
			j = 0;
			while(temp[j] != '\0') {
				strings[strCt] = temp[j];
				strCt++;
				j++;
			}
			// TODO: add a symbol after a string to denote end of a string -> space?
			//strings[k] = "$";
			memset(temp, 0, sizeof temp);
		}
	}

	printf("Num in numbers: \n");
	for(i = 0; i < numCt; i++ ){
		printf(" %d ", numbers[i]);
	}
	i = 0;
	printf("\nContents of strings array: ");
	while(strings[i] != '\0') {
		printf(" %c", strings[i]);
		i++;
	}








	// iterate through buffer checking input

	// need a way to tokenize not just based on space, that wouldn't account for this: if(statement){    -> it would get treated as one
	// maybe add every single individual char to array, then tokenize
	// it would iterate over each array element, if it was a number, it would keep going until it hit a non number
	// it would add the number ^^^ as it's own whole string to 

	// IDEA: initialize char arrays for all different types of tokens
	// I'll need a way to tell the order of tokens going forward to make a compiler
	/*char leftBrackets[10];
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
	}*/

	printf("\n");
	return 0;
}
