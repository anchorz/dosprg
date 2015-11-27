#ifdef __BCC__

#asm
.globl imod
imod:
cwd
idiv bx
mov  ax,dx
ret
#endasm

#endif //__BCC__

