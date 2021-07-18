#include <stdio.h>

int main(int argc, char *argv[]) {
	int i = 123;
	int *p_i = &i;
	printf("Variable i has addr (%p) and value %d\n", &i, i);
	printf("The pointer points to addr (%p) containing value %d\n", p_i, *p_i);
	return 0;
}
