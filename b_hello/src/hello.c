/*
 * example for a simple DOS program that only depends on BIOS calls
 * and do a bit of c-style initializations data or bss segment so 
 * we can verify the memory layout of the compiler
 * 
 * as a small bounus we show an example of a sample printf implementation
 */

#include <stdio.h>

//int foo (char*, ... );

int   s=-32768;
char c; //located in bss section
char *msg="V0.02"; 
int  x; //located in bss section

int main()
{
	c='a';
	x=0xfedc;
	
	printf("this is the kernel %s saying s=%d c='%c' x=0x%x\n",msg,s,c,x);
}