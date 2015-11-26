typedef uint32_t RFS_HANDLE;

typedef struct {
    char *d_name;
    unsigned char d_type;
} RFS_Dirent;

#define RFS_NONE ((RFS_HANDLE)0)
RFS_HANDLE romfs_open_root_directory();
RFS_HANDLE romfs_find_first(RFS_HANDLE directoryHandle);
RFS_HANDLE romfs_find_next(RFS_HANDLE hnd);
void romfs_stat(RFS_HANDLE hnd, RFS_Dirent * dp);

#define T_HLK 0
#define T_DIR 1
#define T_REG 2
