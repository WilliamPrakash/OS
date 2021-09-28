#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
	if(argc == 1) {
		printf("No arguments supplied");
		exit(1);
	} else if(argc >=1) {
		printf("Arguments supplied: ");
		int i = 0;
		while(argv[i] != NULL) {
			printf(" %s ", argv[i]);
			i++;
		}
		printf("\n");
	}
}
