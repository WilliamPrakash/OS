#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

char **ptr;	// global

void *thread(void *vargp);

int main() {
	int i;
	int *j = &i;
	pthread_t tid;
	char *msgs[2] = {
		"Hello from foo",
		"Hello from bar"
	};
	ptr = msgs;
	for (i = 0; i < 2; i++) {
		pthread_create(&tid, NULL, thread,( void *) j);
	};
	pthread_exit(NULL);
}

void *thread(void *vargp) {
	int myid = *((int *)vargp);
	static int svar = 0;

	// Peer threads access main thread's stack indirectly through global ptr variable
	printf("[%d]: %s (svar=%d) \n", myid, ptr[myid], ++svar);
}
