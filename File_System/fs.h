
// meta information about the filesystem
// number of inodes,number of disk blocks, size of disk blocks
struct superblock {
	int num_inodes;
	int num_blocks;
	int size_blocks;
};

struct inode {
	int size;
	int first_block;
	char name[8];
};

// each block will be bigger than 512 bytes, cause each block has a next block pointer
struct disk_block {
	// if we're using an int as the next block num, don't we need a variable to keep track
	// of what block this one is?
	int next_block_num;
	char data[512];
};

void create_fs (); // initialize new file system
void mount_fs ();  // load a file system
void sync_fs ();   // write the file system
int allocate_file(char name[8]); // return filenumber
void print_fs();   // print out info about the filesystem


