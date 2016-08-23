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
  pc->astate = pc->states;

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
    ParserState *next = pc.astate->next(&pc, token);

    if (!next){
      /* Error state encountered */
      fprintf(stderr, "Invalid token encountered\n");
      freeScope(pc.root);
      return NULL;
    }

    /* Check for interstate transitions */
    if (next != pc.astate){
      /* Entering new parser state, so call exit and enter functions */
      if (pc.astate->exit){
        pc.astate->exit(&pc);
      }
      pc.astate = next;
      if (pc.astate->enter){
        pc.astate->enter(&pc);
      }
    }

    /* Process token */
    if (pc.astate->read){
      pc.astate->read(&pc, token);
    }
  }

  /* Return root context */
  return pc.root;
}


/* Initial/Indeterminate state */
ParserState *parstIntrNext(
    Parser *pc,
    Token *token
){
  switch (token->type){
  case TKNST_INTR:
    fprintf(stderr, "Invalid blank token %s\n", token->value);
    return NULL;

  case TKNST_NUMR:
    fprintf(stderr, "Expected identifier before "
      "bare number: %s\n", token->value);
    return NULL;
  }
  return NULL;
}
