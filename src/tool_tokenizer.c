/**
 * Debugger compiler tool that converts gais script to tokens
 * Usage: bin/tool_tokenizer <input script> [output script]
 */

#define _TOOL_ENABLE_TOKENIZER_
#include "tool.h"

void callback(
    Token *tokens,
    Scope *sTree,
    FILE *fout
){
  /* Write tokens to output */
  for (Token *t=tokens; t!=NULL; t=t->next){
    switch (t->type){
    case TKNST_INTR: fprintf(fout, "????????"); break;
    case TKNST_NUMR: fprintf(fout, "Numeric "); break;
    case TKNST_SYMB: fprintf(fout, "Symbol  "); break;
    case TKNST_OPER: fprintf(fout, "Operator"); break;
    case TKNST_MCMT: fprintf(fout, "Comment "); break;
    case TKNST_SCMT: fprintf(fout, "Comment "); break;
    default: fprintf(fout, "UNKOWN");
    }
    fprintf(fout, "\t0x%03X\t%s\n", t->data, t->value);
  }
}


int main(
    int argc,
    char *argv[]
){
  return toolMain(argc, argv, callback);
}
