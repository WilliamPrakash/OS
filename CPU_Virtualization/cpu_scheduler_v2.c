#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <pthread.h>

void *round_robin();
void* initialize_thread(void *input);

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cv;
pthread_key_t glob_var_key;	// value to increment
pthread_key_t glob_var_key_2;	// duplicate for comparison

int thread_ct = 2;	// global count for thread-specific conditional checks
unsigned long int tid_list[2] = {0,0};
int *indx;
int isFirst = 0;
struct thread_data {
	int num;
};


int main(int argc, char *argv[]) {
	pthread_t th[thread_ct];
	pthread_key_create(&glob_var_key, NULL);
	pthread_key_create(&glob_var_key_2, NULL);
	indx = malloc(sizeof(int));
	struct thread_data *info;
	for(int i = 0; i < thread_ct; i++) {
		info = malloc(sizeof(struct thread_data));
		info->num = i;
		if(pthread_create(th + i, NULL, initialize_thread, info) != 0) {
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

void* initialize_thread(void *input) {
	int num;
	struct thread_data *info = input;
	int *inc = malloc(sizeof(int));
	*inc = rand() % 10;
	int* dup = malloc(sizeof(int));
	*dup = *inc + 3;
	tid_list[info->num] = pthread_self();
	if(isFirst == 0) {
		*indx = info->num;
		isFirst += 1;
	}

	// each thread needs two values, one to increment, and a duplicate to compare
	pthread_setspecific(glob_var_key, inc);		// increment
	pthread_setspecific(glob_var_key_2, dup);	// compare
	// running into an issue of which thread created above actually calls this round_robin function
	/* before I call this, I need to make sure both threads are added to the tid_list*/
	/* I'm running into an error where one thread starts execution of round_robin before the other even has a chance to call the function*/
	/* ^^^ this messes up the check of tid_list[*indx], as if a thread is already checking that and the other thread hasn't added to this global variable, then it's checking against nothing*/
	round_robin();
	pthread_setspecific(glob_var_key, NULL);
	pthread_setspecific(glob_var_key_2, NULL);
	free(inc);
	free(dup);
	pthread_exit(NULL);
}

/* this thread sometimes works, sometimes doesn't. I think I'm not checking the order of when threads are added to the tid_list*/
void *round_robin() {
	pthread_cond_init(&cv, NULL);
	// what if a thread is done? it should be removed from the tid_list

	// this might not check values but rather memory address locations
	while(pthread_getspecific(glob_var_key) <= pthread_getspecific(glob_var_key_2) ) {
		printf("next tid to be run: %ld\n", tid_list[*indx]);
		//printf("glob_var_key: %p, glob_var_key_2: %p\n", pthread_getspecific(glob_var_key), pthread_getspecific(glob_var_key_2));
		if( (pthread_mutex_trylock(&mutex) == 0) && (pthread_self() == tid_list[*indx]) ) {
			printf("thread in mutex: %ld\n", pthread_self());
			printf("mutex has been locked, doing stuff\n");
			sleep(3);
			if(*indx == 0) *indx = 1;
			else if(*indx == 1) *indx = 0;
			printf("new value of *indx: %d\n", *indx);

			// increment key
			int* temp = pthread_getspecific(glob_var_key);
			*temp = *temp + 1;
			pthread_setspecific(glob_var_key, temp);
			pthread_cond_signal(&cv);
			pthread_mutex_unlock(&mutex);
		} else {
			pthread_cond_wait(&cv, &mutex);
		}
	}
	printf("exiting while loop...\n");
	pthread_cond_destroy(&cv);
}



