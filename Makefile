# Primary Targets:
# Script Compiler
# Script Disassembler
# Local executor
# Server executor

CFLAGS = -Wall -std=c99 -g
cc = $(CC) $(CFLAGS)


###############################################################################
# Target binary files                                                         #
###############################################################################
all: bin/gais_compiler bin/tool_tokenizer

bin/gais_compiler: obj/lang_compiler.o obj/lang_tokenizer.o
	$(cc) obj/lang_compiler.o obj/lang_tokenizer.o -o bin/gais_compiler

bin/tool_tokenizer: obj/tool_tokenizer.o obj/lang_tokenizer.o
	$(cc) obj/tool_tokenizer.o obj/lang_tokenizer.o -o bin/tool_tokenizer
	

###############################################################################
# Intermediate object files                                                   #
###############################################################################
obj/lang_compiler.o: src/lang_compiler.c src/lang_tokenizer.h
	$(cc) -c src/lang_compiler.c -o obj/lang_compiler.o

obj/lang_tokenizer.o: src/lang_tokenizer.c src/lang_tokenizer.h
	$(cc) -c src/lang_tokenizer.c -o obj/lang_tokenizer.o

obj/tool_tokenizer.o: src/tool_tokenizer.c src/lang_tokenizer.h
	$(cc) -c src/tool_tokenizer.c -o obj/tool_tokenizer.o
