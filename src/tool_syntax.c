/**
 * Debugger compiler tool that converts gais script to syntax tree
 * Usage: bin/tool_syntax <input script> [output script]
 */

#define _TOOL_ENABLE_TOKENIZER_
#define _TOOL_ENABLE_PARSER_
#include "tool.h"

void callback(
    Token *tokens,
    Scope *sTree,
    FILE *fout
){
  
}


int main(
    int argc,
    char *argv[]
){
  return toolMain(argc, argv, callback);
}
