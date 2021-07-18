#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
	int i, size;
	int *p;
	size = 5;
	p = malloc(sizeof(int) * size);
	for (i = 0; i < size; i++) {
	printf("Before init, index %d has value %d at addr (%p)\n", i, p[i], p + i);
	p[i] = i * 2;
	printf("After init, index %d has value %d at addr (%p)\n", i, p[i], p + i);
	}
	return 0;
}
