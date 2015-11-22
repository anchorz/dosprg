#include <stdio.h>

int main(int argc, char **argv)
{
    int i;
    printf("example1 (%s %s)\n",__DATE__,__TIME__);
    
    for (i=0; i<argc;i++)
    {
        printf("argv[%d]=%s \n",i,argv[i]);
    }
    return 0;
}

