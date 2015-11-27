# -I (without arguments) don't add default search path
#                        no need 
# use -Md for dos applications, -Mf "first argument in AX" 
#                        is not applicable, libdos is compiled 
#                        without -Mf
BCC_OPT=-0 -Md -W -ansi -I -Ibcc_include/ -Ih/
LD86_OPT=-i -d -T 0x100 -D 0x0000 -H 0xf000 -m -M

SELF_DIR := $(dir $(lastword $(MAKEFILE_LIST)))
include $(SELF_DIR)common_bcc.mk
