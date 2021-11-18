#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <pthread.h>

void *mutex_test();
void *initialize_thread();

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cv;
pthread_key_t glob_var_key;	// value to increment
pthread_key_t glob_var_key_2;	// duplicate for comparison

int thread_ct = 2;	// global count for thread-specific conditional checks
unsigned long int tid_list[2] = {0,0};
int *indx;

int main(int argc, char *argv[]) {
	pthread_t th[thread_ct];
	pthread_key_create(&glob_var_key, NULL);
	pthread_key_create(&glob_var_key_2, NULL);
	indx = malloc(sizeof(int));
	*indx = 0;
	for(int i = 0; i < thread_ct; i++) {
		if(pthread_create(th + i, NULL, initialize_thread, NULL) != 0) {
			perror("Failed to create thread\n");
			return 1;
		}
	}
	for(int i = 0; i < thread_ct; i++) {
		if(pthread_join(th[i], NULL) != 0) {
			perror("Failed to join thread\n");
                        return 1;
                }
	}
	pthread_mutex_destroy(&mutex);
	exit(0);
}

void *initialize_thread() {
	int *tid = malloc(sizeof(int));
	*tid = rand() % 10; // this doesn't guarantee duplicates
	int* dup = malloc(sizeof(int));
	*dup = *tid + 3;
	int i = 0;
	while(tid_list[i] != 0) {
		i++;
	}
	tid_list[i] = pthread_self();
	// each thread needs two values, one to increment, and a duplicate to compare
	pthread_setspecific(glob_var_key, tid);		// increment
	pthread_setspecific(glob_var_key_2, dup);	// compare
	mutex_test();
	pthread_setspecific(glob_var_key, NULL);
	pthread_setspecific(glob_var_key_2, NULL);
	free(tid);
	free(dup);
	pthread_exit(NULL);
}

void *mutex_test() {
	pthread_cond_init(&cv, NULL);
	
	// the two global variables set in initialize_thread() control how many loops a thread does
	// what if a thread is done? it should be removed from the tid_list!!!!!!

	while(pthread_getspecific(glob_var_key) <= pthread_getspecific(glob_var_key_2) ) {
		printf("value of indx before trylock: %d\n", *indx);
		// maybe make two separate if checks, one for pthread_self and the next for mutex
		if( (pthread_mutex_trylock(&mutex) == 0) && (pthread_self() == tid_list[*indx]) ) {
			printf("mutex has been locked, doing stuff\n");
			sleep(3);
			if(*indx == 0) *indx = 1;
			else if(*indx == 1) *indx = 0;
			printf("value of indx after edits in mutex: %d\n", *indx);

			// increment key
			int* temp = pthread_getspecific(glob_var_key);
			*temp = *temp + 1;
			pthread_setspecific(glob_var_key, temp);
			pthread_cond_signal(&cv);
			pthread_mutex_unlock(&mutex);
		} else {
			pthread_cond_wait(&cv, &mutex);
			indx = 0;
		}
		//printf("1 loop completed: \n");
	}
	printf("exiting while loop...\n");
	pthread_cond_destroy(&cv);
}



