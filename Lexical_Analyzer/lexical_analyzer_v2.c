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
	size_t stringsSize = 32;
	strings = (char *)malloc(stringsSize * sizeof(char));
	int k = 0;
	int l = 0;
	int num;
	char str;
	// iterate through buffer, parsing ints, strings, brackets
	for(i = 0; i < bufCt; i++) {
		if(isdigit(buffer[i])) {
			int j = 0;
			while(isdigit(buffer[i])) {
				temp[j] = buffer[i];
				i++;
				j++;
			}
			// convert temp to an int and add it to numbers array
			sscanf(temp, "%d", &num);
			numbers[k] = num;
			// clear temp 
			memset(temp, 0, sizeof temp);
			k++;
		}
		if(isalpha(buffer[i])) {
			int j = 0;
			while(isalpha(buffer[i])) {
				temp[j] = buffer[i];
				i++;
				j++;
			}
			sscanf(temp, "%c", &str);
			strings[l] = str;
			memset(temp, 0, sizeof temp);
			l++;
		}
	}

	/*printf("Contents of temp ");
	for(i = 0; temp[i] != '\0'; i++){
		printf(" %c  ", temp[i]);
	}*/
	printf("\n");
	for(i = 0; i < k; i++ ){
		printf("Num in members: %d", numbers[i]);
	}
	printf("str: \n", str);
	printf("\n");
	for(i = 0; i < l; i++) {
		printf("String in strings %c", strings[i]);
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
