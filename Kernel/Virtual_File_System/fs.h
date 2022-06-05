
// meta information about the filesystem
// number of inodes,number of disk blocks, size of disk blocks
struct superblock {
	int num_inodes;
	int num_blocks;
	int size_blocks;
};

struct inode {
	int size;
	char name[8];
	int first_block;
};

// each block will be bigger than 512 bytes, cause each block has a next block pointer
struct disk_block {
	int next_block_num;
	char data[512];
};

void create_fs (); // initialize new file system
void mount_fs ();  // load a file system
void sync_fs ();   // write the file system
int allocate_file(char name[8]); // return filenumber
void print_fs();   // print out info about the filesystem



/*
- Before you can access the files on a file system, you need to mount the file system
- Mounting a file system attaches that file system to a directory (mount point) and makes it available to the system
- The root (/) file system is always mounted
- Any other file system can be connected or disconnected from the root file system

*/

