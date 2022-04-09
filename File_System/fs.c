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
	
	// intialize nodes
	int i;
	inodes = malloc(sizeof(struct inode) * sb.num_inodes);
	for(i = 0; i < sb.num_inodes; i++) {
		inodes[i].size = -1;
		inodes[i].first_block = -1;
		strcpy(inodes[i].name, "emptyst");
	}

	// initialize disks
	dsk_blks = malloc(sizeof(struct disk_block) * sb.num_blocks);
	for(i = 0; i < sb.num_blocks; i++) {
		dsk_blks[i].next_block_num = -1;
		// no need to initialize the data here
	}
}


void mount_fs() {
	FILE *file;
	file = fopen("fs_data","r");
	fread(&sb, sizeof(struct superblock), 1, file);

	inodes = malloc(sizeof(struct inode) * sb.num_inodes);
	dsk_blks = malloc(sizeof(struct disk_block) * sb.num_blocks);
	
	fread(inodes, sizeof(struct inode), sb.num_inodes, file);
	fread(dsk_blks, sizeof(struct disk_block), sb.num_blocks, file);
 
	fclose(file);
}

void sync_fs() {
	FILE *file;
	file = fopen("fs_data", "w+");
	
	fwrite(&sb, sizeof(struct superblock), 1, file);
	fwrite(inodes, sizeof(struct inode), sb.num_inodes, file);
	fwrite(dsk_blks, sizeof(struct disk_block), sb.num_blocks, file);

	fclose(file);
}


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


int allocate_file(char name[8]) {

}



