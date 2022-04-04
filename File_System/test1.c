#include <stdio.h>
#include "fs.c"

void main() {
	create_fs();
	sync_fs();
	printf("done\n");
}

