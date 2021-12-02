#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <pthread.h>
#include <stdbool.h>

void *round_robin();
void* initialize_thread(void *input);

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cv;
pthread_cond_t cv1;
pthread_key_t glob_var_key;	// value to increment
pthread_key_t glob_var_key_2;	// duplicate for comparison
bool oneThread = false;

int thread_ct = 2;	// global count for thread-specific conditional checks
unsigned long int tid_list[2] = {0,0};
int *indx;
struct thread_data {
	int num;
};


int main(int argc, char *argv[]) {
	pthread_t th[thread_ct];
	pthread_key_create(&glob_var_key, NULL);
	pthread_key_create(&glob_var_key_2, NULL);
	indx = malloc(sizeof(int));
	*indx = 0;
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
	pthread_setspecific(glob_var_key, inc);		// increment
	pthread_setspecific(glob_var_key_2, dup);	// compare
	pthread_cond_init(&cv1, NULL);
	if(info->num != 0) {
		pthread_cond_wait(&cv1, &mutex1);
	}
	pthread_mutex_unlock(&mutex1);
	pthread_cond_signal(&cv1);
	pthread_cond_destroy(&cv1);
	// i think this only works if the second thread gets there first and immediately goes into waiting
	// actually, I think the way it's written, I need the first thread to execute first always
	// so I have two options, 
	round_robin();
	pthread_setspecific(glob_var_key, NULL);
	pthread_setspecific(glob_var_key_2, NULL);
	free(inc);
	free(dup);
	pthread_exit(NULL);
}


void *round_robin() {
	pthread_cond_init(&cv, NULL);
	// what if a thread is done? it should be removed from the tid_list

	int *temp = pthread_getspecific(glob_var_key);
	int *temp1 = pthread_getspecific(glob_var_key_2);
	// I think I need to move this check to the inside
	while(*temp <= *temp1 ) {
		printf("tid_list[*indx]: %ld    pthread_self(): %ld\n", tid_list[*indx], pthread_self());
		//oneThread = pthread_self() == tid_list[*indx];
		//printf("self = tid_list ? %d\n", oneThread);
		if( (pthread_mutex_trylock(&mutex) == 0) && (pthread_self() == tid_list[*indx] )) {
			printf("thread in mutex: %ld\n", pthread_self());
			printf("mutex has been locked, doing stuff\n");
			if(*indx == 0) *indx = 1;
			else if(*indx == 1) *indx = 0;

			// increment key
			sleep(3);
			int* temp = pthread_getspecific(glob_var_key);
			*temp = *temp + 1;
			pthread_setspecific(glob_var_key, temp);
			pthread_mutex_unlock(&mutex);
			pthread_cond_signal(&cv);
		} else {
			printf("pthread that's currently waiting: %ld\n", pthread_self());
			pthread_cond_wait(&cv, &mutex);
			printf("thread %ld awakened\n", pthread_self());
		}
	}
	printf("exiting while loop...\n");
	//oneThread = true;
	//pthread_cond_destroy(&cv);
}



