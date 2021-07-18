#include <stdio.h>

int pass_by_value(int i) {
	i = i * 2;
	return i;
}

int main(int argc, char *argv[]) {
	int i = 123;
	printf("Value of i before function call: %d\n", i);
	printf("The function returns: %d\n", pass_by_value(i));
	printf("Value of i after function call: %d\n", i);
	return 0;
}
