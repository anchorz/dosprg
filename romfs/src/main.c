#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <errno.h>

#include "romfs.h"

void rep_txt(int count,char *txt)
{
	for (; count--; ) {
		printf("  ");
	}
}

#ifndef __MSDOS__

void iterate_posix(char *name,int depth)
{
	DIR *dir;
	struct dirent *dp;
	char path[256];

	strcpy(path,name);

	rep_txt(depth,"  ");

	printf("[ %s ]\n",name);
	dir=opendir(name);
	if (dir==NULL) {
		printf("opendir failed %d %s\n",errno,strerror(errno));
		return;
	}

	while((dp=readdir(dir))!=NULL) {
		if (strcmp(dp->d_name,".")==0)
			continue;
		if (strcmp(dp->d_name,"..")==0)
			continue;
		if (dp->d_type==DT_DIR) {
			strcat(path,"/");
			strcat(path,dp->d_name);
			iterate_posix(path,depth+1);
			continue;
		}
		rep_txt(depth,"  ");
		if (dp->d_type==DT_REG) {
			printf("%s\n",dp->d_name);
		} else {
			printf("%s of unknown type(%x)\n",dp->d_name,dp->d_type);
		}
	}
	rep_txt(depth,"  ");
	printf("..\n",name);
}
#endif

void iterate(char *name)
{
	void *dir;
	struct romfs_dirent *dp;

	printf("== list of directory: %s ==\n",name);
	dir=romfs_opendir(name);
	while((dp=romfs_readdir(dir))!=NULL) {
		if (strcmp(dp->d_name,".")==0)
			continue;
		if (strcmp(dp->d_name,"..")==0)
			continue;
		if (dp->d_type==T_DIR) {
			printf(" dir: %s\n",dp->d_name);
		}
		if (dp->d_type==T_REG) {
			printf("file: %s\n",dp->d_name);
		} else {
			printf("????: %s %x\n",dp->d_name,dp->d_type);
		}
	}
}

int main()
{
	printf("romfs demo - list files\n");
#ifndef __MSDOS__
	iterate_posix("assets/fs",0);
#endif
	iterate("/");
}
