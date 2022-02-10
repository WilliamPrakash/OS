#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <pthread.h>
#include <stdbool.h>

void *round_robin();

//void* initialize_thread(void *input);
void* initialize_thread();

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cv;
//pthread_key_t glob_var_key;	// value to increment
//pthread_key_t glob_var_key_2;	// duplicate for comparison

/*int thread_ct = 2;	// global count for thread-specific conditional checks
unsigned long int tid_list[2] = {0,0};
int *indx;
struct thread_data {
	int num;
};*/


int main(int argc, char *argv[]) {
	//fflush(stdout);
	pthread_t thread1;
	//pthread_key_create(&glob_var_key, NULL);
	//indx = malloc(sizeof(int));
	//*indx = 0;
	//struct thread_data *info; 
	//for(int i = 0; i < thread_ct; i++) {
	//	info = malloc(sizeof(struct thread_data));
	//	info->num = i;
		if(pthread_create(&thread1, NULL, initialize_thread, NULL) != 0) {
			perror("Failed to create thread\n");
			return 1;
		}
	//}
	//for(int i = 0; i < thread_ct; i++) {
		if(pthread_join(thread1, NULL) != 0) {
			perror("Failed to join thread\n");
                        return 1;
                }
	//}
	pthread_mutex_destroy(&mutex);
	exit(0);
}

//void* initialize_thread(void *input) {
void* initialize_thread() {
	/*int num;
	struct thread_data *info = input;
	int *inc = malloc(sizeof(int));
	*inc = rand() % 10;
	int* dup = malloc(sizeof(int));
	*dup = *inc + 3;
	tid_list[info->num] = pthread_self();
	pthread_setspecific(glob_var_key, inc);		// increment
	pthread_setspecific(glob_var_key_2, dup);	// compare
	if(info->num != 0) {
		//sleep(2);
	}*/
	printf("inside initialize thread\n");
	round_robin();
	/*pthread_setspecific(glob_var_key, NULL);
	pthread_setspecific(glob_var_key_2, NULL);
	free(inc);
	free(dup);*/
	pthread_exit(NULL);
}


void *round_robin() {
	pthread_cond_init(&cv, NULL);
	//int *temp = pthread_getspecific(glob_var_key);
	//int *temp1 = pthread_getspecific(glob_var_key_2);f
	printf("inside round robin\n");
	int inc = 0;
	unsigned int ptd = pthread_self();
	while(inc < 3) {
		//if(pthread_self() == tid_list[*indx]) {
		printf("inside while loop\n");
		//if(pthread_self() == ptd) {
		if(pthread_mutex_trylock(&mutex) == 0) {
			//pthread_mutex_lock(&mutex);
			printf("mutex has been locked, doing stuff\n");

			// increment key
			inc++;
			sleep(3);
			pthread_mutex_unlock(&mutex);
			pthread_cond_signal(&cv);
		} else {
			pthread_cond_wait(&cv, &mutex);
			printf("signaled\n"); // currently, this should never be called
		}
	}
	printf("exiting while loop...\n");
	//pthread_cond_destroy(&cv);
}



