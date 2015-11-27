#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "romfs.h"

extern unsigned char obj_content_bin[];

uint32_t be32_int(uint8_t * ptr)
{
    uint32_t value = *ptr++;
    value *= 256;
    value += *ptr++;
    value *= 256;
    value += *ptr++;
    value *= 256;
    value += *ptr++;
    return value;
}

#define RFS_OFF_VOLUME_FULL_SIZE 8
#define RFS_OFF_VOLUME_CHECKSUM 12
#define RFS_OFF_VOLUME_NAME 16

#define RFS_OFF_DIRENT_NEXT 0
#define RFS_OFF_DIRENT_SPECINFO 4
#define RFS_OFF_DIRENT_NAME 16

RFS_HANDLE romfs_open_root_directory()
{
    uint8_t *start = obj_content_bin;
    int dir_offset = RFS_OFF_VOLUME_NAME;
    start += dir_offset;
    while (*start++)
        dir_offset++;
    dir_offset |= 0xf;
    dir_offset++;
    return dir_offset;
}

void romfs_stat(RFS_HANDLE hnd, RFS_Dirent * dp)
{
    uint8_t *start = obj_content_bin + hnd;
    uint8_t type = *(start + RFS_OFF_DIRENT_NEXT + 3);
    type &= 0x7;
    dp->d_name = (char *)start + RFS_OFF_DIRENT_NAME;
    dp->d_type = type;
}

RFS_HANDLE romfs_find_next(RFS_HANDLE hnd)
{
    uint8_t *start = obj_content_bin + hnd;
    uint32_t dir_offset = be32_int(start + RFS_OFF_DIRENT_NEXT);
    return dir_offset & ~0xf;
}

RFS_HANDLE romfs_find_first(RFS_HANDLE hnd)
{
    uint8_t *start = obj_content_bin + hnd;
    uint8_t type = *(start + RFS_OFF_DIRENT_NEXT + 3);
    uint32_t dir_offset;
    if ((type & 0x7) != T_DIR) {
        return RFS_NONE;
    }
    dir_offset = be32_int(start + RFS_OFF_DIRENT_SPECINFO);
    return dir_offset;
}
