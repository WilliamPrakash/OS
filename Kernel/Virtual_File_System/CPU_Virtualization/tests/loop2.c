#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
	int i;
	for(i=0; i<100; i++) {
		sleep(2);
		printf("loop2 count: %d\n", i);
		// printf is buffered, meaning that the output appears on the console only if you explicitly call fflush(stdout),
		// you print a newline, or the buffer becomes full. Since you don't print a newline until the very end, you will see nothing in the loop.
		// So, either use a newline or fflush(stdout) 
	}
}
