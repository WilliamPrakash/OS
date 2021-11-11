#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <pthread.h>

void *mutex_test();
void *roll();
void *timer();
void *tls_values();
void *do_stuff();
void *initialize_thread();

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cv;
pthread_key_t glob_var_key;

// Theads have 3 states: running, ready, blocked

int main(int argc, char *argv[]) {
	pthread_t th[2];
	pthread_key_create(&glob_var_key, NULL);

	for(int i = 0; i < 2; i++) {
		if(pthread_create(th + i, NULL, initialize_thread, NULL) != 0) {
			perror("Failed to create thread\n");
			return 1;
		}
		printf("Thread %d created\n", i);
	}
	for(int i = 0; i < 2; i++) {
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
	pthread_setspecific(glob_var_key, tid);
	mutex_test();
	pthread_setspecific(glob_var_key, NULL);
	free(tid);
	pthread_exit(NULL);
}

void *mutex_test() {
	int* tid = pthread_getspecific(glob_var_key);
	printf("unique thread value: %d\n", *tid);
	pthread_cond_init(&cv, NULL);
	//while(1) {
	//while(*tid != *tid + 1) {
		if(pthread_mutex_trylock(&mutex) == 0) {
			pthread_mutex_lock(&mutex);
			printf("mutex has been locked\nPerforming a task for 3 seconds...\n");
			sleep(3);
			pthread_mutex_unlock(&mutex);
			printf("unlocked\n");
			pthread_cond_signal(&cv);
			//*tid += 1;
        	} else {
			printf("pausing other thread while waiting for mutex to be unlocked\n");
			pthread_cond_wait(&cv, &mutex); // this will wait for a signal from another thead
			printf("other thread has been resumed\n");
        	}
	//}
	pthread_cond_destroy(&cv);
}



/****	Reference code for TLS	****/
void *do_stuff() {
        // get thread specific data
        int* glob_spec_var = pthread_getspecific(glob_var_key);
        printf("Thread %d before mod value is %d\n", (unsigned int) pthread_self(), *glob_spec_var);
        *glob_spec_var += 1;
        printf("Thread %d after mod value is %d\n", (unsigned int) pthread_self(), *glob_spec_var);
}

void *tls_values() {
        int *p = malloc(sizeof(int));
        *p = rand() % 10;
        printf("Address of p for thread %d: %p\n", (unsigned int) pthread_self(), p);
        pthread_setspecific(glob_var_key, p); // i think the only way this works is if glob_var_key is unique to each thread
        do_stuff();
        do_stuff();
        pthread_setspecific(glob_var_key, NULL); // why is this called? oh I think I'm clearing out the value associated with glob_var_key since I'm creating this var on the heap
        free(p);
        pthread_exit(NULL);
}
