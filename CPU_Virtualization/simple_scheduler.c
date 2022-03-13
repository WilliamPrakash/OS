#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <pthread.h>
#include <stdbool.h>

void *simple_switcher();
void* initialize_thread();
void* clean();

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cv;

int inc = 0;
int i = 0;
long unsigned int pidList[2] = {0,0};

int main(int argc, char *argv[]) {
	//clean();
	pthread_t threads[2];
	for(int i = 0; i < 2; i++) {
		if(pthread_create(&threads[i], NULL, initialize_thread, NULL) != 0) {
			perror("Failed to create thread\n");
			return 1;
		}
	}
	for(int i = 0; i < 2; i++) {
		if(pthread_join(threads[i], NULL) != 0) {
			perror("Failed to join thread\n");
                        return 1;
                }
	}
	pthread_mutex_destroy(&mutex);
	exit(0);
}

void* initialize_thread() {
	simple_switcher();
	//pthread_exit(NULL);
}

void *simple_switcher() {
	pthread_cond_init(&cv, NULL);
	while(pidList[i] != 0) i++;
	pidList[i] = pthread_self();
	i = 0;
	while(inc < 3) {
		printf("pidList[i]: %ld\n", pidList[i]);
		if(pthread_self() == pidList[i] && pthread_mutex_trylock(&mutex) == 0) {
			if (i == 0) i = 1;
			else if (i == 1) i = 0;
			printf("mutex has been locked by: %ld\n", pthread_self());
			int check = pthread_mutex_trylock(&mutex);
			// OH! I think i isn't being changed quick enough, so the other thread is checking a "stale" i value, resulting in the else condition not working
			// I could signal the other thread here with yet another condition variable to let it know the i is updated
			inc++;
			sleep(3);
			pthread_cond_signal(&cv);
			pthread_mutex_unlock(&mutex);
		} else { 
			printf("thread waiting on condition signal: %ld\n", pthread_self());
			pthread_cond_wait(&cv, &mutex);
			printf("signaled\n");
		}
	}
	printf("exiting while loop...\n");
	clean();
}

void* clean() {
	pthread_cond_destroy(&cv);
}


/*void* initialize_thread() {
        int num;
        struct thread_data *info = input;
        int *inc = malloc(sizeof(int));
        *inc = rand() % 10;
        int* dup = malloc(sizeof(int));
        *dup = *inc + 3;
        tid_list[info->num] = pthread_self();
        pthread_setspecific(glob_var_key, inc);         // increment
        pthread_setspecific(glob_var_key_2, dup);       // compare
        if(info->num != 0) {
                //sleep(2);
        }
        round_robin();
        pthread_setspecific(glob_var_key, NULL);
        pthread_setspecific(glob_var_key_2, NULL);
        free(inc);
        free(dup);
        pthread_exit(NULL);
}*/
