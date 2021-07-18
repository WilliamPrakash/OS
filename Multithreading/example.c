#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

void * workerThreadFunc(void * tid){
	long * myId = (long *) tid;
	printf("Hello world! This is thread: %ld\n", *myId);
}


int main(){
	pthread_t tid0;	// uniquely identifies a thread
	pthread_t tid1;
	pthread_t tid2;
	pthread_t * pthreads[] = {&tid0, &tid1, &tid2};

	for(int i = 0; i < 3; i++){
		pthread_create(pthreads[i], NULL, workerThreadFunc,(void *)pthreads[i] );
	}

	//pthread_create(&tid0, NULL, workerThreadFunc,(void *)&tid0 );	// 2 arg: you can pass in attributes;	3 arg: give thread a piece of code to execute; 4 arg: args for 3 arg

	pthread_exit(NULL);	// forces main thread to wait until created thread is finished executing
	return 0;
}

