/**
 * Debugger compiler tool that converts gais script to syntax tree
 * Usage: bin/tool_syntax <input script> [output script]
 */
#include <stdlib.h>
#include <stdio.h>

#include "lang_tokenizer.h"


#define CLEANUP_MAIN fcleanup(&fin, &fout, &tokens)
#define CLEANUP_MAIN_FAILURE CLEANUP_MAIN; return EXIT_FAILURE
#define CLEANUP_MAIN_SUCCESS CLEANUP_MAIN; return EXIT_SUCCESS


/**
 * Helper function to cleanup main()'s top-level data structures
 */
void fcleanup(
    FILE **fin,
    FILE **fout,
    Token **tokens
){
  if (*fin){
    fclose(*fin);
    *fin = NULL;
  }

  if (*fout){
    fclose(*fout);
    *fout = NULL;
  }

  if (*tokens){
    freeTokens(*tokens);
    *tokens = NULL;
  }
}


int main(
    int argc,
    char *argv[]
){
  char *fileName;
  FILE *fin=NULL;
  FILE *fout=NULL;
  Token *tokens=NULL;

  if (argc!=2 && argc!=3){
    fprintf(stderr, "Usage: %s <input script> [output file]\n", argv[0]);
    CLEANUP_MAIN_FAILURE;
  }

  /* Get file handles */
  fileName = argv[1];
  fin = fopen(fileName, "r");
  if (!fin){
    fprintf(stderr, "Error, cannot open file '%s'\n", fileName);
    CLEANUP_MAIN_FAILURE;
  }
  if (argc == 3){
    fileName = argv[2];
    fout = fopen(fileName, "w");
    if (!fout){
      fprintf(stderr, "Error, cannot open file '%s'\n", fileName);
      CLEANUP_MAIN_FAILURE;
    }
  } else {
    fout = stdout;
  }

  /* Tokenize input stream */
  tokens = tokenizeStream(fin);
  if (!tokens){
    fprintf(stderr, "Error in tokenization\n");
    CLEANUP_MAIN_FAILURE;
  }

  /* Build syntax tree from tokens */


  CLEANUP_MAIN_SUCCESS;
}
