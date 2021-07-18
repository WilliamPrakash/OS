#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
	char str[100];
	printf("Enter a value :");
	scanf("%s", str);
	getchar();
	printf("\nYou entered: %s\n", str);

	return 0;
}
