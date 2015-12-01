#ifdef __MSDOS__

#asm
.text
entry startup

startup:
	mov ax,cs
	add ax,#__segoff
	mov ds,ax
	mov es,ax

	mov ss,ax
	mov sp,#0xfffe
		
	mov		bx,#0xffff ; new size - try to get all
	mov		ah,#0x4A  ; resize memory block
	int		0x21

.zap_bss:
	cld
	mov di,#__edata
	mov cx,#__end
	sub cx,di
	shr cx,1
	xor ax,ax
	rep 
		stosw

	call _main
	int  0x20
#endasm

#else
typedef int __AVOID_PEDANTIC;
#endif