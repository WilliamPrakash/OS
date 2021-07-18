#include <stdio.h>

int main(int argc, char *argv[]) {
	int i = 123;
	printf("Variable i has addr (%p) and value %d\n", &i, i);
	return 0;
}
