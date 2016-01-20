# Primary Targets:
# Script Compiler
# Script Disassembler
# Local executor
# Server executor

CFLAGS = -Wall -std=c99 -g
cc = $(CC) $(CFLAGS)

# Language header and object files
hdrLang = src/lang.h src/lang_tokenizer.h src/lang_syntax.h
objLang = obj/lang.o obj/lang_tokenizer.o obj/lang_syntax.o


###############################################################################
# Target binary files                                                         #
###############################################################################
all: bin/gais_compiler bin/tool_syntax bin/tool_tokenizer

bin/gais_compiler: obj/tool_compiler.o $(objLang)
	$(cc) obj/tool_compiler.o $(objLang) -o bin/gais_compiler

bin/tool_syntax: obj/tool_syntax.o $(objLang)
	$(cc) obj/tool_syntax.o $(objLang) -o bin/tool_syntax

bin/tool_tokenizer: obj/tool_tokenizer.o $(objLang)
	$(cc) obj/tool_tokenizer.o $(objLang) -o bin/tool_tokenizer
	

###############################################################################
# Intermediate object files                                                   #
###############################################################################
obj/lang.o: src/lang.c $(hdrLang)
	$(cc) -c src/lang.c -o obj/lang.o

obj/lang_syntax.o: src/lang_syntax.c $(hdrLang)
	$(cc) -c src/lang_syntax.c -o obj/lang_syntax.o

obj/lang_tokenizer.o: src/lang_tokenizer.c $(hdrLang)
	$(cc) -c src/lang_tokenizer.c -o obj/lang_tokenizer.o

obj/tool_compiler.o: src/tool_compiler.c $(hdrLang)
	$(cc) -c src/tool_compiler.c -o obj/tool_compiler.o

obj/tool_syntax.o: src/tool_syntax.c $(hdrLang)
	$(cc) -c src/tool_syntax.c -o obj/tool_syntax.o

obj/tool_tokenizer.o: src/tool_tokenizer.c $(hdrLang)
	$(cc) -c src/tool_tokenizer.c -o obj/tool_tokenizer.o
