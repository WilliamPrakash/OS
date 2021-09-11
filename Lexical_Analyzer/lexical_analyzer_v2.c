#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>

int main(int argc, char *argv[]) {
	printf("type a string to be tokenized: ");
	char *buffer;
	size_t bufsize = 32;
	buffer = (char *)malloc(bufsize * sizeof(char));
	getline(&buffer, &bufsize, stdin);
	int i = 0;
	int bufCt = 0;
	// Iterate through buffer to make sure everything inputted is in here
	printf("Contents of buffer: ");
	for (i = 0; buffer[i] != '\0'; i++){
		printf(" %c  ", buffer[i]);
		bufCt++;
	}
	printf("\n");

	// Pointers for holding numbers, characters, and brackets
	// TODO: I really need a way to keep all this in one array, or at least a way to remember the order of everyting
	char *temp;
	size_t tempSize = 32;
	temp = (char *)malloc(tempSize * sizeof(char));
	int *numbers;
	size_t numbersSize = 32;
	numbers = (int *)malloc(numbersSize * sizeof(int));
	char *strings;
	size_t stringsSize = 100;
	strings = (char *)malloc(stringsSize * sizeof(char));
	int numCt = 0;
	int strCt = 0;	// this isn't actually a string count, it's a char count
	int num;
	char leftBrackets[10] = {0,0,0,0,0,0,0,0,0,0}; // uninitialized variables can have unpredictable contents, do this to basically assign it values to overwrite
	char rightBrackets[10] = {0,0,0,0,0,0,0,0,0,0};
	int leftBracCount = 0;
	int rightBracCount = 0;
	
	// Iterate through buffer, parsing every single char one at a time
	// If it hits a number or english letter, it will keep going to get entire word/number
	for(i = 0; i < bufCt; i++) {
		// Grabs all numbers
		// NOTE: this won't account for decimals
		if(isdigit(buffer[i])) {
			int j = 0;
			while(isdigit(buffer[i])) {
				temp[j] = buffer[i];
				i++;
				j++;
			}
			i--;	// decrement i cause it was incremented above ^^^
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
			strings[strCt] = '$';
			strCt++;
			memset(temp, 0, sizeof temp);
		}
		// Grab all left brackets
		else if( buffer[i] == '(' || buffer[i] == '[' || buffer[i] == '{') {
                        leftBrackets[leftBracCount] = buffer[i];
    			leftBracCount++;
                }
		// Grab all right brackets
		else if(buffer[i] == ')' || buffer[i] == ']' || buffer[i] == '}') {
			rightBrackets[rightBracCount] = buffer[i];
			rightBracCount++;
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
	i = 0;
	printf("\nContents of Bracket arrays: ");
	while(leftBrackets[i] != 0) {
		printf(" %c", leftBrackets[i]);
		i++;
	}
	i = 0;	
	while(rightBrackets[i] != 0) {
		printf(" %c", rightBrackets[i]);
		i++;
	}

	/*** Token Checking  ***/

	// Check brackets:
	// TODO: first check to see if len of right and left bracket arrays are equal
	// then make sure they match up


	/*************** END  ***************/
	printf("\n");
	return 0;
}
