#include <stdio.h>

int pass_by_ref(int *a_pointer) {
	*a_pointer = (*a_pointer) * 2;
	return *a_pointer;
}

int main(int argc, char *argv[]) {
	int i = 123;
	printf("Value of i before function call: %d\n", i);
	printf("The function returns: %d\n", pass_by_ref(&i));
	printf("Value of i after function call:%d\n", i);
	return 0;
}
