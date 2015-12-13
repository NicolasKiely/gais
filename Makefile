# Primary Targets:
# Script Compiler
# Script Disassembler
# Local executor
# Server executor

CFLAGS = -Wall -std=c99
cc = $(CC) $(CFLAGS)


###############################################################################
# Target binary files                                                         #
###############################################################################
bin/compiler: obj/lang_compiler.o
	$(cc) obj/lang_compiler.o -o bin/compiler
	

###############################################################################
# Intermediate object files                                                   #
###############################################################################
obj/lang_compiler.o: src/lang_compiler.c
	$(cc) -c src/lang_compiler.c -o obj/lang_compiler.o