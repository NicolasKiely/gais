#include <stdlib.h>
#include "lang_syntax.h"


/*****************************************************************************\
| Scoped Syntax Tree                                                          |
\*****************************************************************************/
Scope *newScope()
{
  Scope *s = malloc(sizeof(Scope));

  return s;
}


void freeScope(
    Scope *sTree
){
  free(sTree);
}


/*****************************************************************************\
| Syntax Tree Context                                                         |
\*****************************************************************************/
void initializeParserContext(
    Parser *pc
){
  pc->root = newScope();

  /* Initial/Indeterminate state */
  pc->states[PARST_INTR].enter = NULL;
  pc->states[PARST_INTR].exit = NULL;
  pc->states[PARST_INTR].read = NULL;
  pc->states[PARST_INTR].next = parstIntrNext;
}


/*****************************************************************************\
| Parser                                                                      |
\*****************************************************************************/
Scope *parseTokens(
    Token *token
){
  Parser pc;

  initializeParserContext(&pc);

  /* Loop over tokens */
  for (; token != NULL; token = token->next){
    /* Get next parsing state for given token */
    // ***getNextParseState()

    // Error check parse state

    /* Check for interstate transitions */

    /* Process token */
  }

  /* Return root context */
  return pc.root;
}
