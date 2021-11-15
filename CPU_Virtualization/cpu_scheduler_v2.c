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
void *force_thread_sleep();

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cv;
pthread_key_t glob_var_key;	// value to increment
pthread_key_t glob_var_key_2;	// duplicate for comparison

int thread_ct = 2;	// global count for thread-specific conditional checks
unsigned long int tid_list[2] = {0,0};

int main(int argc, char *argv[]) {
	pthread_t th[thread_ct];
	pthread_key_create(&glob_var_key, NULL);
	pthread_key_create(&glob_var_key_2, NULL);
	
	for(int i = 0; i < thread_ct; i++) {
		if(pthread_create(th + i, NULL, initialize_thread, NULL) != 0) {
			perror("Failed to create thread\n");
			return 1;
		}
		/****	can't do this here, i think it's only adding main thread	****/
		/*tid_list[i] = pthread_self();
		printf("Thread %ld currently executing...\n", pthread_self());
		printf("Thread %ld added to tid_list\n", tid_list[i]);*/
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
	*dup = *tid;
	printf("tid for thread %ld: %d\n", pthread_self(), *tid);
	//
	int i = 0;
	while(tid_list[i] != 0) {
		i++;
	}
	tid_list[i] = pthread_self();
	printf("thread %ld added to tid_list\n", tid_list[i]);
	
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

int indx = 0;
void *mutex_test() {
	//int* tid = pthread_getspecific(glob_var_key);
	int* dup = pthread_getspecific(glob_var_key_2);
	*dup = *dup + 3;
	pthread_setspecific(glob_var_key_2, dup);
	pthread_cond_init(&cv, NULL);
	
	while(pthread_getspecific(glob_var_key) <= pthread_getspecific(glob_var_key_2) ) {
		printf("value of indx before trylock: %d\n", indx);
		if( (pthread_mutex_trylock(&mutex) == 0) && (pthread_self() == tid_list[indx]) ) {
			printf("mutex has been locked, doing stuff\n");
			/**  this will only work for two threads, need to use thread_ct  **/
			printf("value of indx: %d\n", indx);
			/*if(indx >= 1) {
				printf("skjdgfa jysgdfgasjdfgs\n");
				indx = 0;
			} else {*/
				indx = 1;
			//}
			sleep(3);

			// increment
			int* temp = pthread_getspecific(glob_var_key);
			*temp = *temp + 1;
			pthread_setspecific(glob_var_key, temp);
			printf("glob_var_key for thread %ld: %d\n", pthread_self(), *temp);
			printf("unlocked\n");
			pthread_cond_signal(&cv);
			pthread_mutex_unlock(&mutex);
		} else {
			pthread_cond_wait(&cv, &mutex);
			indx = 0;
		}
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
