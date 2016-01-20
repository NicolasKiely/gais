#include "lang_syntax.h"


Scope *newScope()
{
  Scope *s = malloc(sizeof(Scope));

  return s;
}


Scope *parseTokens(
    Token *token
){
  Scope *sTree = NULL;

  /* Loop over tokens */
  for (; token != NULL; token = token->next)

  }

  return sTree;
}


void freeScope(
    Scope *sTree
){
  free(sTree);
}
