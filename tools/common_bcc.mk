.PHONY: directories

all: directories $(EXECUTABLE) $(EXECUTABLE).com
	$(POST_BUILD)
	
$(EXECUTABLE): $(addprefix obj/gcc/,$(OBJECTS))
	gcc $^ -o $@ $(addprefix -l,$(LIBS))

$(EXECUTABLE).com: $(addprefix obj/bcc/,$(BCC_OBJECTS)) $(addprefix obj/bcc/,$(OBJECTS))
	ld86 $(LD86_OPT) $(addprefix -l,$(LIBS)) $+ -o $@ | sort -k 4 1>obj/bcc/$(EXECUTABLE).lnk 

obj/bcc/%.o: src/%.c
	bcc $(BCC_OPT) -S -o $@.asm $<
	bcc $(BCC_OPT) -c -o $@ $<

obj/gcc/%.o: src/%.c
	gcc -c -Wall -pedantic -std=c99 -O0 -o $@ -Ih/ $<
	
directories:
	@mkdir -p obj/bcc
	@mkdir -p obj/gcc
	
clean:
	rm -f  h/*~
	rm -f  src/*~
	rm -rf obj/
	@if [ -f $(EXECUTABLE).com ]; then rm $(EXECUTABLE).com; fi
	@if [ -f $(EXECUTABLE).exe ]; then rm $(EXECUTABLE).exe; fi
	@if [ -f $(EXECUTABLE) ]; then rm $(EXECUTABLE); fi