struct romfs_dirent
{
	unsigned char d_type;
	char d_name[256];
};

#define T_HLK 0
#define T_DIR 1
#define T_REG 2

void *romfs_opendir(char *);
struct romfs_dirent *romfs_readdir(void *dir);