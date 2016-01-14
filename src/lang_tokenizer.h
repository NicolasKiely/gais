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
#define OPER_MCMT -1 // Multi-line comment detected
#define OPER_NONE 0x00 // Initial operation
#define OPER_EXCL 0x01 // ! 
#define OPER_HASH 0x02 // #
#define OPER_SYS  0x03 // $
#define OPER_MOD  0x04 // %
#define OPER_AMP  0x05 // &
#define OPER_OPRN 0x06 // (
#define OPER_CPRN 0x07 // )
#define OPER_STAR 0x08 // *
#define OPER_PLUS 0x09 // +
#define OPER_COM  0x0A // ,
#define OPER_DASH 0x0B // -
#define OPER_DOT  0x0C // .
#define OPER_FSLS 0x0D // /
#define OPER_CLN  0x0E // :
#define OPER_SCLN 0x0F // ;
#define OPER_LT   0x10 // <
#define OPER_EQ   0x11 // =
#define OPER_GT   0x12 // >
#define OPER_HUH  0x13 // ?
#define OPER_AT   0x14 // @
#define OPER_OBRK 0x15 // [
#define OPER_BSLS 0x16 // Backslash
#define OPER_CBRK 0x17 // ]
#define OPER_CRT  0x18 // ^
#define OPER_OCRL 0x19 // {
#define OPER_PIPE 0x1A // |
#define OPER_CCRL 0x1B // }
#define OPER_TLD  0x1C // ~

/* Comment states */
#define CMNT_START 0 // Start of comment
#define CMNT_TEXT  1 // Middle of comment
#define CMNT_STAR  2 // * symbol encountered
#define CMNT_DONE  3 // */ encountered


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

  /* Token type */
  char type;

  /* Misc token data */
  int data;

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

  /* Misc state data */
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

// Comment state

/** Token state enter callback for comments */
void tknstCmntEnter(
    void *context
);

/** Token state read callback for comments */
void tknstCmntRead(
    int c,
    void *context
);

/** Token state switch callback for comments */
struct tokenState *tknstCmntNext(
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

/**
 * Sets token's initial state from given character
 * @param c First operator character
 * @param t Token of operator
 */
void operatorInitState(
    int c,
    Token *t
);


#endif
