#ifdef __BCC__

int putchar(int c)
{
#asm
	cmp al,#0x0a
	jne .no_newline
	push ax
	mov ax,#0x0e0d
	xor bx,bx
	int $10
	pop ax
.no_newline:
	mov ah,#0x0e
	xor bx,bx
	int $10
#endasm
}
#else
typedef int __AVOID_PEDANTIC;
#endif