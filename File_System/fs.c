#include "fs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct superblock sb;
struct inode *inodes;
struct disk_block *dbs;

void create_fs() {
	// setup superblock
	sb.num_inodes = 10;
	sb.num_blocks = 100;
	sb.size_blocks = sizeof(struct disk_block);
	
	int i;

	// initialize nodes
	inodes = malloc(sizeof(struct inode) * sb.num_inodes);
	for(i = 0; i < sb.num_inodes; i++) {
		inodes[i].size = -1;
		// arguments: (destination, source)
		strcpy(inodes[i].name, "");
	}

	// initialize disks
	dbs = malloc(sizeof(struct disk_block) * sb.num_blocks);
	for(i = 0; i < sb.num_blocks; i++) {
		dbs[i].next_block_num = -1;
		// no need to initialize the data here
	}
}

void mount_fs() {

}

void sync_fs() {
	FILE *file;
	file = fopen("fs_data", "w+");
	
	// superblock
	fwrite(&sb, sizeof(struct superblock), 1, file);

	// inodes
	int i;
	for(i = 0; i < sb.num_inodes; i++) {
        	fwrite(&inodes[i], sizeof(struct inode), 1, file);
        }

        // initialize disks
        dbs = malloc(sizeof(struct disk_block) * sb.num_blocks);
        for(i = 0; i < sb.num_blocks; i++) {
		fwrite(&dbs[i], sizeof(struct disk_block), 1, file);
        }
	fclose(file);
}





