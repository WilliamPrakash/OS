#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

// invoke this with command line arguments equal to the amount of cores your cpu has
// ubuntu command: (./cpu A &); (./cpu B &); (./cpu C &); (./cpu D &); (./cpu E &); (./cpu F &);
// mac command: (./cpu A &); (./cpu B &); (./cpu C &); (./cpu D &); (./cpu E &); (./cpu F &); (./cpu G &); (./cpu H &);

int main(int argc, char *argv[]){
	if(argc != 2){
		fprintf(stderr, "usage: cpu <string>\n");
		exit(1);
	}
	char *str = argv[1];

	while(1){
		printf("%s\n", str);
		//Spin(1);
		//pthread_spin_init();	// this shit isn't working
	}
	return 0;
}
