/**
 * Header file for misc tool functions
 */
#ifndef _TOOL_H_
#define _TOOL_H_

#include <stdlib.h>
#include <stdio.h>
#include "lang_tokenizer.h"
#include "lang_syntax.h"

/* Cleanup macros for main() */
#define CLEANUP_MAIN fcleanup(&fin, &fout, &tokens, &sTree)
#define CLEANUP_MAIN_FAILURE CLEANUP_MAIN; return EXIT_FAILURE
#define CLEANUP_MAIN_SUCCESS CLEANUP_MAIN; return EXIT_SUCCESS


/**
 * Helper function to cleanup main()'s top-level data structures
 */
void fcleanup(
    FILE **fin,
    FILE **fout,
    Token **tokens,
    Scope **sTree
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

  if (*sTree){
    freeScope(*sTree);
    *sTree = NULL;
  }
}


/**
 * Main function for tool scripts
 * Will invoke tokenizer if _TOOL_ENABLE_TOKENIZER_ is defined
 * Will invoke parser if _TOOL_ENABLE_PARSER_ is defined
 * @param argc Number of program arguments
 * @param argv Program arguments
 * @param callback Optional callback function invoked after compilation
 * @return Program exit status
 */
int toolMain(
    int argc,
    char *argv[],
    void (*callback)(Token *, Scope *, FILE *)
){
  char *fileName;
  FILE *fin=NULL;
  FILE *fout=NULL;
  Token *tokens=NULL;
  Scope *sTree=NULL;

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

  #ifdef _TOOL_ENABLE_TOKENIZER_
  /* Tokenize input stream */
  tokens = tokenizeStream(fin);
  if (!tokens){
    fprintf(stderr, "Error in tokenization\n");
    CLEANUP_MAIN_FAILURE;
  }
  #endif

  #ifdef _TOOL_ENABLE_PARSER_
  /* Build syntax tree from tokens */
  sTree = parseTokens(tokens);
  if (!sTree){
    fprintf(stderr, "Error in parsing\n");
    CLEANUP_MAIN_FAILURE;
  }
  #endif

  /* Invoke callback if requested */
  if (callback){
    callback(tokens, sTree, fout);
  }

  CLEANUP_MAIN_SUCCESS;
}
#endif
