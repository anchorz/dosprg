.PHONY: directories

all: directories $(EXECUTABLE) $(EXECUTABLE).com
	$(POST_BUILD)
	
$(EXECUTABLE): $(addprefix obj/gcc/,$(OBJECTS))
	gcc $^ -o $@ $(addprefix -l,$(LIBS))

$(EXECUTABLE).com: $(addprefix obj/bcc/,$(OBJECTS))
	ld86 -i -d -T 0x100 -D 0x0000 -H 0xf000  -L../bcc/lib/ -m -M ../bcc/lib/crt0.o -ldos $(addprefix -l,$(LIBS)) $+ -o $@ | sort -k 4 1>obj/bcc/$(EXECUTABLE).lnk 
	
obj/bcc/%.o: src/%.c
# use -Md for dos applications
# -Mf "first argument in AX" not applicable, libdos is compiled without
	bcc -0 -S -Md -W -o $@.asm -ansi  -I../bcc/include/ -Ih/  $<
	bcc -0 -c -Md -W -o $@ -ansi -I../bcc/include/ -Ih/  $<

obj/gcc/%.o: src/%.c
	gcc -c -Wall -pedantic -std=c99 -O0 -o $@ -Ih/ $<
	
directories:
	@mkdir -p obj/bcc
	@mkdir -p obj/gcc
	
clean:
	rm -f  src/*~
	rm -rf obj/
	@if [ -f $(EXECUTABLE).com ]; then rm $(EXECUTABLE).com; fi
	@if [ -f $(EXECUTABLE).exe ]; then rm $(EXECUTABLE).exe; fi
	@if [ -f $(EXECUTABLE) ]; then rm $(EXECUTABLE); fi

