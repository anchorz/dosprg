EXECUTABLE=romfs
OBJECTS= main.o romfs.o content.o

include ../tools/generics_bcc.mk

obj/content.bin:
	genromfs -f obj/content.bin -d assets/fs -V 0123456789abcdef 

src/content.c: obj/content.bin
	xxd -i obj/content.bin obj/content.c
