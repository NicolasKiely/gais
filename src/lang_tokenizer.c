#include <ctype.h>
#include <stdlib.h>

#include "lang_tokenizer.h"


/*****************************************************************************\
| Token Node List                                                             |
\*****************************************************************************/
Token *newToken()
{
  Token *t = malloc(sizeof(Token));
  t->len = 0;
  t->size = TOKEN_INIT_SIZE;
  t->value = malloc(t->size);
  t->next = NULL;

  return t;
}


void freeTokens(
    Token *token
){
  Token *next;

  while (token){
    next = token->next;
    if (token->value){
      free(token->value);
    }
    free(token);
    token = next;
  }
}


/*****************************************************************************\
| Tokenization Context                                                        |
\*****************************************************************************/
void initializeTokenContext(
    TokenContext *tc
){
  tc->root = NULL;
  tc->last = NULL;
  tc->state = tc->states + TKNST_INTR;

  /* Initial/Intersymbolic state */
  tc->states[TKNST_INTR].enter = NULL;
  tc->states[TKNST_INTR].exit = NULL;
  tc->states[TKNST_INTR].readChar = NULL;
  tc->states[TKNST_INTR].nextState = tknstIntrNext;

  /* Numeric state */
  tc->states[TKNST_NUMR].enter = tknstTknEnter;
  tc->states[TKNST_NUMR].exit = tknstNumrExit;
  tc->states[TKNST_NUMR].readChar = tknstTknRead;
  tc->states[TKNST_NUMR].nextState = tknstNumrNext;

  /* Symbolic state */
  tc->states[TKNST_SYMB].enter = tknstTknEnter;
  tc->states[TKNST_SYMB].exit = tknstSymbExit;
  tc->states[TKNST_SYMB].readChar = tknstTknRead;
  tc->states[TKNST_SYMB].nextState = tknstSymbNext;

  /* Operator state */
  tc->states[TKNST_OPER].enter = tknstOperEnter;
  tc->states[TKNST_OPER].exit = tknstOperExit;
  tc->states[TKNST_OPER].readChar = tknstOperRead;
  tc->states[TKNST_OPER].nextState = tknstOperNext;

  /* Comment state */
  /*
  tc->states[TKNST_CMNT].enter = tknstCmntEnter;
  tc->states[TKNST_CMNT].exit = tknstCmntExit;
  tc->states[TKNST_CMNT].readChar = tknstCmntRead;
  tc->states[TKNST_CMNT].nextState = tknstCmntNext;
  */
}


/*****************************************************************************\
| Tokenization Code                                                           |
\*****************************************************************************/
Token *tokenizeStream(
    FILE *fin
){
  TokenContext tc;
  int c;

  initializeTokenContext(&tc);

  while ((c=fgetc(fin)) != EOF){
    /* Get current tokenization state */
    TokenState *nextState = tc.state->nextState(c, &tc);
    if (!nextState){
      /* Error encountered */
      fprintf(stderr, "Invalid token encountered\n");
      if (tc.root){
        freeTokens(tc.root);
      }
      return NULL;
    }

    if (nextState != tc.state){
      /* Entering new tokenization state */
      if (tc.state->exit){
        tc.state->exit(&tc);
      }
      if (nextState->enter){
        nextState->enter(&tc);
      }
      tc.state = nextState;
    }

    /* Process input */
    if (tc.state->readChar){
      tc.state->readChar(c, &tc);
    }
  }

  return tc.root;
}


/* Initial/Intersymbolic state */
TokenState *tknstIntrNext(
    int c,
    void *context
){
  TokenContext *tc = (TokenContext *) context;

  if (isspace(c)){
    return tc->state + TKNST_INTR;

  } else if (isdigit(c)) {
    return tc->state + TKNST_NUMR;

  } else if (isoperator(c)) {
    return tc->state + TKNST_OPER;

  } else {
    return tc->state + TKNST_SYMB;
  }

  //return NULL;
}


/* Generic state */
void tknstTknEnter(
    void *context
){
  TokenContext *tc = (TokenContext *) context;
  if (!tc->root){
    /* First symbol */
    tc->root = newToken();
    tc->last = tc->root;

  } else {
    tc->last->next = newToken();
    tc->last = tc->last->next;
  }
}


void tknstTknRead(
    int c,
    void *context
){
  TokenContext *tc = (TokenContext *) context;
  Token *t = tc->last;
  /* Append character to last token */
  t->value[t->len] = (char) c;
  t->len++;

  if (t->len+1 >= t->size){
    /* Resize buffer if full */
    t->size *= 2;
    t->value = realloc(t->value, t->size);
  }
}


/* Numberic state */
void tknstNumrExit(
  void *context
){
  TokenContext *tc = (TokenContext *) context;
  Token *t = tc->last;
  t->value[t->len] = '\0';
  printf("Numeric token: %s\n", t->value);
}


struct tokenState *tknstNumrNext(
    int c,
    void *context
){
  TokenContext *tc = (TokenContext *) context;

  if (isspace(c)){
    return tc->states + TKNST_INTR;
  } else if (isoperator(c) && c!='.'){
    return tc->states + TKNST_OPER;
  } else {
    return tc->states + TKNST_NUMR;
  }
}


/* Symbolic state */
void tknstSymbExit(
    void *context
){
  TokenContext *tc = (TokenContext *) context;
  Token *t = tc->last;
  t->value[t->len] = '\0';
  printf("Symbol token: %s\n", t->value);
}


struct tokenState *tknstSymbNext(
    int c,
    void *context
){
  TokenContext *tc = (TokenContext *) context;

  if (isspace(c)){
    return tc->states + TKNST_INTR;

  } else if (isoperator(c)){
    return tc->states + TKNST_OPER;

  } else {
    return tc->states + TKNST_SYMB;
  }
}


/* Operator state */
void tknstOperEnter(
    void *context
){
  TokenContext *tc = (TokenContext *) context;
  tknstTknEnter(context);

  tc->state->data = OPER_NONE;
}


void tknstOperExit(
    void *context
){
  TokenContext *tc = (TokenContext *) context;
  Token *t = tc->last;
  t->value[t->len] = '\0';
  printf("Operator token: %s\n", t->value);
}


void tknstOperRead(
    int c,
    void *context
){
  tknstTknRead(c, context);
}


struct tokenState *tknstOperNext(
    int c,
    void *context
){
  TokenContext *tc = (TokenContext *) context;

  if (isspace(c)){
    return tc->states + TKNST_INTR;

  } else if (isalpha(c)){
    return tc->states + TKNST_SYMB;

  } else if (isdigit(c)){
    return tc->states + TKNST_NUMR;

  } else {
    /* Check if symbol or operator */
    return tc->states + TKNST_OPER;
  }
}


/* Comment state */


/* Misc helper functions for tokenizer */
int isoperator(
    int c
){
  switch (c){
    case '!':
    case '$':
    case '%':
    case '&':
    case '(':
    case ')':
    case '*':
    case '+':
    case '-':
    case '.':
    case '/':
    case ';':
    case '<':
    case '=':
    case '>':
    case '^':
    case '{':
    case '}':
    return 1;
  }
  return 0;
}
