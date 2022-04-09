#include <stdio.h>
#include "fs.c"

void main() {
	create_fs();
	sync_fs();
	//mount_fs();
	print_fs();
	printf("done\n");
}

