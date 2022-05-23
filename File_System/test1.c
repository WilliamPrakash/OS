#include <stdio.h>
#include "fs.c"

void main() {
	// create filesystem
	//create_fs();
	//sync_fs();

	char str[20];
	int i;
	printf("Enter a string and an int:   ");
	scanf("%s %d", str, &i);	
	printf("\nYou entered: %s %d ", str, i);
	// always need to mount it before performing any action on it
	// except maybe printing it?
	mount_fs();
	allocate_file("first");
	sync_fs();
	// syncing after allocating a file, and running the program multiple times without
	// compiling, gives a good demonstration of how the sync_fs funct works
	print_fs();
	printf("done\n");
}

