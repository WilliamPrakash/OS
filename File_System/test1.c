#include <stdio.h>
#include "fs.c"

void main() {
	create_fs();
	sync_fs();
	mount_fs();
	allocate_file("first");
	print_fs();
	printf("done\n");
}

