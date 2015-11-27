static void md2fast_transform(MD2FAST_CTX *ctx)
{
#asm
	push bp
	mov bx,#_s
#if __FIRST_ARG_IN_AX__
	mov si,ax
	mov bp,ax
#else
	mov bp,sp
	mov si,[bp+4]
	mov bp,si
#endif
	lea di,[bp+32]
	mov cx,#8
m4:	
	lodsw
	stosw
	xor ax,[di-18]
	mov [di+14],ax
	dec cx
	jnz m4
	
	xor ax,ax
	mov dx,ax
	mov si,#18
m2:
	lea di,[bp+16]
	mov cx,#12
m1:
	xlatb 
	xor al,[di]
	stosb 
	xlatb 
	xor al,[di]
	stosb 	
	xlatb 
	xor al,[di]
	stosb 
	xlatb 
	xor al,[di]
	stosb 	
	dec cx
	jnz m1

	add ax,dx
	inc dx
	dec si
	jnz m2
	lea si,[di+15]
	lodsb

	mov si,bp
	mov cx,#16
m3:
	xchg ah,al
	lodsb 
	xor al,ah
	xlatb
	xor al,[di]
	stosb
	dec cx
	jnz m3
	pop bp
	#endasm
}

