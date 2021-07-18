#include <stdio.h>

int main(int argc, char *argv[]) {
	int numbers[5];
	int i;
	for (i = 0; i < 5; i++) {
	numbers[i] = i * 2;
	printf("Index %d has value %d at address (%p)\n", i, numbers[i], (numbers + i));
	}
	return 0;
}
