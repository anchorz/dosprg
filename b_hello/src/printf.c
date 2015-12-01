#include <stdio.h>
#include <stdarg.h>

#ifdef __BCC__
  #define const
#endif //__BCC__  

void prints(char *s)
{
	char c;

	while( (c=*s) ) {
		putchar(c);
		s++;
	}
}


void printi(int i)
{
	int a=i;

	if (i<0) {
		putchar('-');
		a=-(a%10);
		printi(-(i/10));
	}
	if (i>9) {
		printi(i/10);
		a=i%10;
	}
	putchar('0'+ a );
}

void printx(unsigned int i)
{
	int a=i;

	if (i>16) {
		printx(i>>4);
		a=i&0xf;
	}
	if (a>9) {
		a+=39;
	}
	putchar('0'+ a );
}

int printf(const char *fmt, ... )
{
	va_list ap;
	char *s,c;
	int d;

	va_start(ap,fmt);
	while (*fmt) {
		c=*fmt++;
		if (c!='%') {
			putchar(c);
			continue;
		}
		c=*fmt++;
		switch (c) {
		case 's':
			s = va_arg(ap, char *);
			prints(s);
			break;
		case 'd':
			d = va_arg(ap, int);
			printi(d);
			break;
		case 'c':
			c = (char) va_arg(ap, int);
			putchar(c);
			break;
		case 'x':
			d = va_arg(ap, int);
			printx(d);
			break;
		default:
			break;
		}

	}
	va_end(ap);
	return 0;
}
