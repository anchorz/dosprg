UNAME := $(shell uname -mo)

ifeq ("$(UNAME)", "x86_64 Cygwin")
	export PATH := $(PATH):$(shell pwd)/tools/w64
endif

SUBPROJECTS=crc b_hello romfs example1 crc32sum md2sum

all:
	for dir in $(SUBPROJECTS);do pwd; cd $$dir; make || exit 2 ; cd ..; done

clean:
	cd ./bcc; make clean;
	for dir in $(SUBPROJECTS);do pwd; cd $$dir; make clean; cd ..; done
