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
pthread_key_t glob_var_key;	// value to increment
pthread_key_t glob_var_key_2;	// duplicate for comparison

// Theads have 3 states: running, ready, blocked

int main(int argc, char *argv[]) {
	pthread_t th[2];
	pthread_key_create(&glob_var_key, NULL);
	pthread_key_create(&glob_var_key_2, NULL);

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
	int* dup = malloc(sizeof(int));
	*dup = *tid;
	printf("tid for thread %ld: %d\n", pthread_self(), *tid);
	pthread_setspecific(glob_var_key, tid);		// increment
	pthread_setspecific(glob_var_key_2, dup);	// compare
	//free(tid);
	//free(dup);
	mutex_test();
	pthread_setspecific(glob_var_key, NULL);
	pthread_setspecific(glob_var_key_2, NULL);
	free(tid);
	free(dup);
	pthread_exit(NULL);
}

void *mutex_test() {
	//int* tid = pthread_getspecific(glob_var_key);
	int* dup = pthread_getspecific(glob_var_key_2);
	*dup = *dup + 3;
	pthread_setspecific(glob_var_key_2, dup);
	pthread_cond_init(&cv, NULL);
	
	// THIS DOESN'T SWITCH THREADS
	// it has one fully execute before releasing it to the other thread 
	while(pthread_getspecific(glob_var_key) <= pthread_getspecific(glob_var_key_2) ) {
		pthread_mutex_lock(&mutex);
			printf("mutex has been locked, doing stuff\n");
			sleep(3);
			// increment
			int* temp = pthread_getspecific(glob_var_key);
			*temp = *temp + 1;
			pthread_setspecific(glob_var_key, temp);
			printf("glob_var_key for thread %ld: %d\n", pthread_self(), *temp);
			
			printf("unlocked\n");
			pthread_cond_signal(&cv);
			pthread_mutex_unlock(&mutex);
		pthread_cond_wait(&cv, &mutex);
		printf("1 loop completed: \n");

	}
	printf("exiting while loop...\n");
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
