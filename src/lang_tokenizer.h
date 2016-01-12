#ifndef _LANG_TOKENIZER_H_
#define _LANG_TOKENIZER_H_

#include <stdio.h>

/** Initial token buffer size */
#define TOKEN_INIT_SIZE 8

/** Token state indices */
#define TKNST_INTR 0
#define TKNST_NUMR 1
#define TKNST_SYMB 2
#define TKNST_OPER 3
#define TKNST_CMNT 4
#define TKNST_COUNT 5

/** Operator indices */
#define OPER_NONE 0


/*****************************************************************************\
| Token Node List                                                             |
\*****************************************************************************/
typedef struct tokenNode
{
  /* Token buffer */
  char *value;

  /* Token string length */
  int len;

  /* Allocated buffer size */
  int size;

  /* Pointer to next token in list */
  struct tokenNode *next;
} Token;


/**
 * Creates newly allocated token ready for writing
 * @return Newly allocated token
 */
Token *newToken();

/**
 * Frees a list of tokens, including root node
 * @param token Pointer to root token to free
 */
void freeTokens(
  Token *token
);


/*****************************************************************************\
| Tokenization Context                                                        |
\*****************************************************************************/
typedef struct tokenState
{
  /* Callback function when state first entered */
  void (*enter)(void *context);

  /* Callback function when state exitted */
  void (*exit)(void *context);

  /* Callback function for reading a single character */
  void (*readChar)(int c, void *context);

  /* Callback function for getting next state */
  struct tokenState *(*nextState)(int c, void *context);

  /* Misc data variable for states to use */
  int data;
} TokenState;


typedef struct tokenContext
{
  /* First and last token nodes */
  Token *root;
  Token *last;

  TokenState states[TKNST_COUNT];
  TokenState *state;

} TokenContext;


/**
 * Initializes a token context state
 * @param tc Tokenization context
 */
void initializeTokenContext(
    TokenContext *tc
);


/*****************************************************************************\
| Tokenization Code                                                           |
\*****************************************************************************/
/**
 * Builds token list from input stream
 * Caller is responsible for freeing token list
 * @param fin Input file stream
 * @return Serial list of tokens
 */
Token *tokenizeStream(
    FILE *fin
);


/** Inter-symbol jump state */
TokenState *tknstIntrNext(
    int c,
    void *context
);

// Generic token state
/**
 * Token state entry callback function for token builders
 * Creates a new token at the end of the token list
 */
void tknstTknEnter(
    void *context
);

/**
 * Read callback for token builders
 * Appends character to token, and reallocates if necessary
 */
void tknstTknRead(
    int c,
    void *context
);

// Numeric token state 
/**
 * Exit callback numeric tokens
 */
void tknstNumrExit(
    void *context
);

/**
 * State switch callback for numeric tokens
 */
struct tokenState *tknstNumrNext(
    int c,
    void *context
);

// Symbol token state

/**
 * Exit callback symbol tokens
 * Caps token string with null terminator so it can be used as c-string
 */
void tknstSymbExit(
    void *context
);

/**
 * State switch callback for symbol tokens
 */
struct tokenState *tknstSymbNext(
    int c,
    void *context
);

// Operator token state

/** Token state entry callback for operators */
void tknstOperEnter(
    void *context
);

/** Token state exit callback for operators */
void tknstOperExit(
    void *context
);

/** Token state read callback for operators */
void tknstOperRead(
    int c,
    void *context
);

/** Token state switch callback for operators */
struct tokenState *tknstOperNext(
    int c,
    void *context
);

// Token misc functions
/** 
 * Determines whether or not a character is a valid operator
 * @return 1 if operator, 0 otherwise
 */
int isoperator(
    int c
);


#endif
