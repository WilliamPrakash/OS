#include "fs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct superblock sb;
struct inode *inodes;
struct disk_block *dsk_blks;

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
		inodes[i].first_block = -1;
		strcpy(inodes[i].name, "");
	}

	// initialize disks
	dsk_blks = malloc(sizeof(struct disk_block) * sb.num_blocks);
	for(i = 0; i < sb.num_blocks; i++) {
		dsk_blks[i].next_block_num = -1;
		// no need to initialize the data here
	}
}

// you can think of mounting as "read"
void mount_fs() {
	FILE *file;
	file = fopen("fs_data","r");

	// read in superblock
	fread(&sb, sizeof(struct superblock), 1, file);

	// read in inodes
	int i;
	for(i = 0; i < sb.num_inodes; i++) {
		fread(&(inodes[i]), sizeof(struct inode), 1, file);
	}

	// read in data on disk blocks
	for(i = 0; i < sb.num_blocks; i++) {
		fread(&dsk_blks[i], sizeof(struct disk_block), 1, file);
	}
}

// you can think of sync as "write"
void sync_fs() {
	FILE *file;
	file = fopen("fs_data", "w+");
	
	// write to superblock
	fwrite(&sb, sizeof(struct superblock), 1, file);

	// write inodes
	int i;
	for(i = 0; i < sb.num_inodes; i++) {
        	fwrite(&inodes[i], sizeof(struct inode), 1, file);
        }

        // write initialize disks
        dsk_blks = malloc(sizeof(struct disk_block) * sb.num_blocks);
        for(i = 0; i < sb.num_blocks; i++) {
		fwrite(&dsk_blks[i], sizeof(struct disk_block), 1, file);
        }
	fclose(file);
}

// print out info about the filesystem
void print_fs() {
	printf("Superblock info\n");
	printf("\tnum inodes: %d\n", sb.num_inodes);
	printf("\tnum blocks: %d\n", sb.num_blocks);
	printf("\tsize blocks: %d\n", sb.size_blocks);

	printf("inodes\n");
	int i;
	for(i = 0; i < sb.num_inodes; i++) {
		printf("\tsize: %d   first block: %d   name: %s\n", inodes[i].size, inodes[i].first_block, inodes[i].name);
	}

	for(i = 0; i < sb.num_blocks; i++) {
		printf("\tblock num: %d next block %d\n", i, dsk_blks[i].next_block_num);
	}

}
















