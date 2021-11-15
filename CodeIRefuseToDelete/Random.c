#include <stdlib.h>
#include <stdio.h>
#include <time.h>


void *roll() {
        int value = (rand() % 6) + 1;
        int *result = malloc(sizeof(int));
        *result = value;
        return (void*) result;  // you can't return a reference to a local variable, will be deallocated
}





void *timer() {
        clock_t before, after;
        before = clock();       // this gets the number of clock ticks that have elapsed since the program was launched
        sleep(8);
        after = clock();
        double t1 = ( (double)(after-before) ) / CLOCKS_PER_SEC;
        printf("clock after: %f\n", t1);
}
