#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <fcntl.h>
#include <unistd.h>
#include <zlib.h>

#define VERSION_STR "1.00.0005"

void usage()
{
    printf("Print CRC32 checksums\n");
    printf("usage: crc32sum <FILE>...\n\n");
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

void crc32sum(char *filename)
{
    int len;
    int fh=open(filename,O_RDONLY);
    unsigned long crc=0;

    if (fh==-1)
    {
        printf("%s: No such file or directory\n",filename);
        return;
    }
    do
    {
        len=read(fh,transferbuffer,TRANSFER_SIZE);
        if (len>0)
        {
            crc=crc32(crc,transferbuffer,len);
        }
    } while(len==TRANSFER_SIZE);

    printf("%8lx *%s\n",crc,filename);
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
        crc32sum(argv[i]);
    }
    
    return 0;
}
