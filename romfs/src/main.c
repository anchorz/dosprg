#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include "romfs.h"

void iterate(int depth, RFS_HANDLE hnd, char *path)
{
    RFS_Dirent dp;

    printf("d: %s\n", path);
    do {
        romfs_stat(hnd, &dp);
        if (strcmp(dp.d_name, ".") == 0) {
            continue;
        }
        if (strcmp(dp.d_name, "..") == 0) {
            continue;
        }
        if (dp.d_type == T_DIR) {
            char new_path[256];
            strcpy(new_path, path);
            strcat(new_path, dp.d_name);
            strcat(new_path, "/");
            iterate(depth + 1, romfs_find_first(hnd), new_path);
            continue;
        }
        printf("f: %s%s\n", path, dp.d_name);
    } while ((hnd = romfs_find_next(hnd)) != RFS_NONE);
}

int main()
{
    RFS_HANDLE hnd;

    printf("romfs demo - list files\n");
    hnd = romfs_open_root_directory();
    iterate(0, hnd, "/");
}
