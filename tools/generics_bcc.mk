# use -Md for dos applications, -Mf "first argument in AX" 
#                        is not applicable, libdos is compiled 
#                        without -Mf
BCC_OPT=-0 -Md -W -ansi -I../bcc/include/ -Ih/
LD86_OPT= -i -d -T 0x100 -D 0x0000 -H 0xf000  -L../bcc/lib/ -m -M ../bcc/lib/crt0.o -ldos

SELF_DIR := $(dir $(lastword $(MAKEFILE_LIST)))
include $(SELF_DIR)common_bcc.mk
