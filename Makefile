SUBPROJECTS=b_hello romfs example1 crc32sum md2sum

all:
	for dir in $(SUBPROJECTS);do pwd; cd $$dir; make ; cd ..; done

clean:
	cd ./bcc; make clean;
	for dir in $(SUBPROJECTS);do pwd; cd $$dir; make clean; cd ..; done
