#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//C File Handling
//1. Stream-oriented data files - the data is stored in the same manner as it appears on the screen
//2. System-oriented data files - the data files are more closely associated with the OS

//C file Operations:
//creation, opening, reading, write data, closing

//Steps for Processing a File
//1. Declare a file pointer variable
//2. Open a file using fopen()
//3. Process the file using the suitable function
//4. Close the file using fclose()

// fopen(), fclose(), getc(), putc(), getw(), putw(), fprintf(), fscanf(), fgets(), fputs(), feof()

int main()
{
	FILE *fp;
	// if file doesn't exist, a new name with the specified name will be created
	fp = fopen("test1.txt", "w");
	// processing of the file(s)
	fprintf(fp, "%s", "written from basic.c\n");
	// end of processing
	fclose(fp);
	return 0;
}

