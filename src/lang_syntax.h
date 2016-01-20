#ifndef _LANG_SYNTAX_H_
#define _LANG_SYNTAX_H_

#include "lang_tokenizer.h"

/*****************************************************************************\
| Scoped Syntax Tree                                                          |
\*****************************************************************************/
/**
 * Syntatic scope block
 */
typedef struct Scope
{
  /* Parent Scope */
  struct Scope *parent;
} Scope;


/**
 * Creates a newly allocated scope object
 */
Scope *newScope();


/**
 * Frees a Syntax Scope Tree
 * @param token Pointer to root token to free
 */
void freeScope(
    Scope *sTree
);


/*****************************************************************************\
| Parser                                                                      |
\*****************************************************************************/
/**
 * Parse tokens into syntax tree
 * @param token Root token to parse
 */
Scope *parseTokens(
    Token *token
);


#endif
