#include <stdio.h>
#include <stdlib.h>

int y;
int z = 10;

int main(int argc, char *argv[]){
  printf("Memory locations: \n");
  printf("- code: %p\n", (void *) main);
  printf("- data: %p\n", (void *) &z);
  printf("- bss : %p\n", (void *) &y);
  printf("- heap: %p\n", (void *) malloc(sizeof(int)));
  printf("- heap: %p\n", (void *) malloc(10 * sizeof(int)));
  printf("- heap: %p\n", (void *) malloc(sizeof(float)));
  int x = 3;
  printf("Memory locations (stack): \n");
  printf("- x   : %p\n", (void *) &x);
  float w = 6;
  printf("- w   : %p\n", (void *) &w);
  float i = 10.0;
  printf("- i   : %p\n", (void *) &i);
  return 0;
}
