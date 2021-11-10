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

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cv;
pthread_key_t glob_var_key;

// Theads have 3 states: running, ready, blocked

int main(int argc, char *argv[]) {
	pthread_t th[2];
	pthread_key_create_(&global_var_key, NULL);

	int *res = malloc(sizeof(int));
	srand(time(NULL));

	for(int i = 0; i < 2; i++) {
		if(pthread_create(th + i, NULL, tls_values, NULL) != 0) {
			perror("Failed to create thread\n");
			return 1;
		}
		printf("Thread %d created\n", i);
	}
	for(int i = 0; i < 2; i++) {
		if(pthread_join(th[i], NULL) != 0) {
		//if(pthread_join(th[i], (void**) &res) != 0) {
			perror("Failed to join thread\n");
                        return 1;
                }
		//printf("Result: %d\n", *res);
		//free(res);
	}
	pthread_mutex_destroy(&mutex);
	exit(0);
}

void *do_stuff() {
	// get thread specific data
        int* glob_spec_var = pthread_getspecific(glob_var_key);
        printf("Thread %d before mod value is %d\n", (unsigned int) pthread_self(), *glob_spec_var);
        *glob_spec_var += 1;
        printf("Thread %d after mod value is %d\n", (unsigned int) pthread_self(), *glob_spec_var);
}

void *tls_values() {
	int *p = malloc(sizeof(int));
	*p = 1;
	printf("Address of p for thread %d: %p\n", (unsigned int) pthread_self(), p);
        pthread_setspecific(glob_var_key, p); // i think the only way this works is if glob_var_key is unique to each thread 
	do_stuff();
	do_stuff();
	pthread_setspecific(glob_var_key, NULL); // why is this called? oh I think I'm clearing out the value associated with glob_var_key since I'm creating this var on the heap
        free(p);
        pthread_exit(NULL);
}

void *mutex_test() {
	pthread_cond_init(&cv, NULL);
	// TODO: Pause thread execution and giving it to another
	// i need a variable that's specific to each thread if I wanna make a loop
	//while(1) {
		if(pthread_mutex_trylock(&mutex) == 0) {
			pthread_mutex_lock(&mutex);
			printf("mutex has been locked\nPerforming a task for 3 seconds...\n");
			sleep(3);
			pthread_mutex_unlock(&mutex);
			printf("unlocked\n");
			pthread_cond_signal(&cv);
        	} else {
			printf("pausing other thread while waiting for mutex to be unlocked\n");
			pthread_cond_wait(&cv, &mutex); // this will wait for a signal from another thead
			printf("other thread has been resumed\n");
        	}
	//}
	pthread_cond_destroy(&cv);
}

