#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>
#include <fcntl.h>
#include <unistd.h>

#include "md2fast.h"

#define VERSION_STR "1.00.0006"

void usage()
{
	printf("Print MD2 (128-bit) checksums\n");
	printf("usage: md2sum <FILE>...\n\n");
	printf("  --help     display this help and exit\n");
	printf("  --version  output version information and exit\n");
}

int check_options_quit(int argc, char **argv)
{
	int i;
	
	for (i=1; i<argc; i++)
	{
		if (strcmp(argv[i],"--version")==0)
		{
			printf("%s",VERSION_STR);
			return true;
		}
		if (strcmp(argv[i],"--help")==0)
		{
			usage();
			return true;
		}
	}
	return false;
}

int check_options_ok(int argc, char **argv)
{
	int i;
	
	for (i=1; i<argc; i++)
	{
		if (*argv[i]!=0 && *argv[i]=='-')
		{
			printf("unknown option %s\n",argv[i]);
			printf("Try '--help' for more information.\n");
			return false;
		}
	}
	return true;
}

#define TRANSFER_SIZE 1024*16
static uint8_t transferbuffer[TRANSFER_SIZE];

MD2FAST_CTX ctx_fast;

void md2sum(char *filename)
{
	int i,len;
	int fh=open(filename,O_RDONLY);
	uint8_t hash[16];

	md2fast_init(&ctx_fast);
	if (fh==-1)
	{
		printf("%s: No such file or directory\n",filename);
		return;
	}
	do
	{
		len=read(fh,transferbuffer,TRANSFER_SIZE);
		md2fast_update(&ctx_fast,transferbuffer, len);
	} while(len==TRANSFER_SIZE);

	md2fast_final(&ctx_fast,hash);
	for (i=0; i<16; i++)
	{
		printf("%02x",hash[i]);
	}
	printf(" *%s\n",filename);
}

int main(int argc,char **argv)
{
	int i;
	
	if (argc==1)
	{
		usage();
		return 0;
	}
	
	if (check_options_quit(argc,argv))
	{
		return 0;
	}
	
	if (!check_options_ok(argc,argv))
	{
		return 1;
	}

	for (i=1; i<argc; i++)
	{
		md2sum(argv[i]);
	}
	
	return 0;
}