#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "romfs.h"

extern unsigned char obj_content_bin[];

unsigned int be32_int(uint8_t *ptr)
{
	unsigned int value=*ptr++;
	value*=256;
	value+=*ptr++;
	value*=256;
	value+=*ptr++;
	value*=256;
	value+=*ptr++;	
	return value;
}

//static uint8_t *dir;
static unsigned int dir_offset;
static struct romfs_dirent dp;

void * romfs_opendir(char *dir)
{
	if (strcmp(dir,"/")==0)
	{
	uint8_t *start=obj_content_bin;
	start+=16;
	while(*start++);
	dir_offset=(start-obj_content_bin);	
	dir_offset|=0xf;
	dir_offset++;
	return (void*)obj_content_bin;
	}
	return NULL;
}

struct romfs_dirent *romfs_readdir(void *dir)
{
	unsigned int mode;
	uint8_t *this_dir;
	
	if (dir_offset==0)
	{
		return NULL;
	}
	
	this_dir=(uint8_t*)dir+dir_offset;
	dir_offset=be32_int(this_dir);
	mode=dir_offset&0xf; //ignore bit3 - executable bit
	dp.d_type=mode&0x7;
	dir_offset&=~0xf; 
	strcpy(dp.d_name,(char*)this_dir+16);
	return &dp;
}