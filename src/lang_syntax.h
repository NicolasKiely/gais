#ifndef _LANG_SYNTAX_H_
#define _LANG_SYNTAX_H_

#include "lang_tokenizer.h"

/** Parser state indices */
#define PARST_INTR 0
#define PARST_COUNT 1


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
| Syntax Tree Context                                                         |
\*****************************************************************************/
typedef struct parserContext Parser;
typedef struct parserState ParserState;

/** Parser state */
struct parserState
{
  /* Callback function for entering state */
  void (*enter)(Parser *pc);

  /* Callback function for exiting state */
  void (*exit)(Parser *pc);

  /* Callback function for processing a token */
  void (*read)(Parser *pc, Token *t);

  /* Callback function for determing next token state */
  ParserState *(*next)(Parser *pc, Token *t);
};


/** Parser Context */
struct parserContext
{
  /* Root parsing scope */
  Scope *root;

  /* Array of parser states */
  ParserState states[PARST_COUNT];
};

/**
 * Initializes the parser context
 * @param pc Parser context
 */
void initializeParserContext(
    Parser *pc
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
