#ifndef _LANG_TOKENIZER_H_
#define _LANG_TOKENIZER_H_

#include <stdio.h>

/** Initial token buffer size */
#define TOKEN_INIT_SIZE 8

/** Token state indices */
#define TKNST_INTR  0
#define TKNST_NUMR  1
#define TKNST_SYMB  2
#define TKNST_OPER  3
#define TKNST_MCMT  4
#define TKNST_SCMT  5
#define TKNST_COUNT 6

/** Operator indices */
#define OPER_SCMT -2 // Single-line comment detected
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
/* Compound operators */
#define OPER_EXCL_EQ 0x1D // !=
#define OPER_MOD_EQ  0x1E // %=
#define OPER_STAR_EQ 0x1F // *=
#define OPER_PLUS_EQ 0x20 // +=

/* Comment states */
#define CMT_START 0 // Start of comment
#define CMT_TEXT  1 // Middle of comment
#define CMT_STAR  2 // * symbol encountered
#define CMT_DONE  3 // */ encountered

/* Key words (from ANSI C standard) */
#define KW_NON  0x00 // Not a keyword
#define KW_ASM  0x01 // Asm - not supported
#define KW_AUT  0x02 // Auto - not supported
#define KW_BRK  0x03 // Break
#define KW_CASE 0x04 // Case
#define KW_CHAR 0x05 // Char
#define KW_CNST 0x06 // const - not supported
#define KW_CONT 0x07 // Continue
#define KW_DFLT 0x08 // Default
#define KW_DO   0x09 // Do
#define KW_DBL  0x0A // Double
#define KW_ELSE 0x0B // Else
#define KW_ENUM 0x0C // Enum - not supported
#define KW_EXTN 0x0D // extern - not supported
#define KW_FLT  0x0E // Float
#define KW_FOR  0x0F // For
#define KW_GOTO 0x10 // Goto - not supported
#define KW_IF   0x11 // If
#define KW_INT  0x12 // Int
#define KW_LONG 0x13 // Long
#define KW_REG  0x14 // Register - not supported
#define KW_RET  0x15 // Return
#define KW_SHRT 0x16 // Short
#define KW_SGN  0x17 // Signed
#define KW_SZOF 0x18 // Sizeof
#define KW_STTC 0x19 // Static
#define KW_STRC 0x1A // Struct
#define KW_SWTC 0x1B // Switch
#define KW_TPDF 0x1C // Typedef - not supported
#define KW_UNN  0x1D // Union - not supported
#define KW_USGN 0x1E // Unsigned
#define KW_VOID 0x1F // Void
#define KW_VLT  0x20 // Volatile - not supported
#define KW_WHL  0x21 // While
#define KW_COUNT 0x21 // Number of keywords

/* Key words array */
typedef struct keyWord {
  char *word;
} KeyWord;
extern KeyWord KEY_WORDS[];


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

  /* Pointer to previous token in list */
  struct tokenNode *prev;
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
typedef struct tokenContext TokenContext;

typedef struct tokenState
{
  /* Callback function when state first entered */
  void (*enter)(TokenContext *tc);

  /* Callback function when state exitted */
  void (*exit)(TokenContext *tc);

  /* Callback function for reading a single character */
  void (*readChar)(int c, TokenContext *tc);

  /* Callback function for getting next state */
  struct tokenState *(*nextState)(int c, TokenContext *tc);

  /* Misc state data */
  int data;
} TokenState;


struct tokenContext
{
  /* First and last token nodes */
  Token *root;
  Token *last;

  TokenState states[TKNST_COUNT];
  TokenState *state;

};


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
    TokenContext *tc
);

// Generic token state
/**
 * Token state entry callback function for token builders
 * Creates a new token at the end of the token list
 */
void tknstTknEnter(
    TokenContext *tc
);

/**
 * Read callback for token builders
 * Appends character to token, and reallocates if necessary
 */
void tknstTknRead(
    int c,
    TokenContext *tc
);

// Numeric token state 
/**
 * Exit callback numeric tokens
 */
void tknstNumrExit(
    TokenContext *tc
);

/**
 * State switch callback for numeric tokens
 */
struct tokenState *tknstNumrNext(
    int c,
    TokenContext *tc
);

// Symbol token state

/**
 * Exit callback symbol tokens
 * Caps token string with null terminator so it can be used as c-string
 */
void tknstSymbExit(
    TokenContext *tc
);

/**
 * State switch callback for symbol tokens
 */
struct tokenState *tknstSymbNext(
    int c,
    TokenContext *tc
);

// Operator token state

/** Token state entry callback for operators */
void tknstOperEnter(
    TokenContext *tc
);

/** Token state exit callback for operators */
void tknstOperExit(
    TokenContext *tc
);

/** Token state read callback for operators */
void tknstOperRead(
    int c,
    TokenContext *tc
);

/** Token state switch callback for operators */
struct tokenState *tknstOperNext(
    int c,
    TokenContext *tc
);

// Comment state

/** Token state enter callback for comments */
void tknstCmtEnter(
    TokenContext *tc
);

/** Token state read callback for multi-line comments */
void tknstMCmtRead(
    int c,
    TokenContext *tc
);

/** Token state read callback for single-line comments */
void tknstSCmtRead(
    int c,
    TokenContext *tc
);

/** Token state switch callback for comments */
struct tokenState *tknstCmtNext(
    int c,
    TokenContext *tc
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

/**
 * Rewinds token context by one token. Assumes at least one
 * token exists.
 * @param tc Token context
 */
void rewindToken(
    TokenContext *tc
);

/**
 * Looks up id of reserved keyword
 * @param value String to lookup
 * @return 1+index of keyword, or 0 if not found
 */
int lookupKeywordID(
    char *value
);

#endif
