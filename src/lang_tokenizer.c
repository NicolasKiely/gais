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
  t->prev = NULL;
  t->data = 0;
  t->type = -1;

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
  tc->states[TKNST_MCMT].enter = tknstCmtEnter;
  tc->states[TKNST_MCMT].exit = NULL;
  tc->states[TKNST_MCMT].readChar = tknstMCmtRead;
  tc->states[TKNST_MCMT].nextState = tknstCmtNext;

  tc->states[TKNST_SCMT].enter = tknstCmtEnter;
  tc->states[TKNST_SCMT].exit = NULL;
  tc->states[TKNST_SCMT].readChar = tknstSCmtRead;
  tc->states[TKNST_SCMT].nextState = tknstCmtNext;
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
    TokenContext *tc
){
  if (isspace(c)){
    return tc->states + TKNST_INTR;

  } else if (isdigit(c)) {
    return tc->states + TKNST_NUMR;

  } else if (isoperator(c)) {
    return tc->states + TKNST_OPER;

  } else {
    return tc->states + TKNST_SYMB;
  }

  //return NULL;
}


/* Generic state */
void tknstTknEnter(
    TokenContext *tc
){
  Token *t = newToken();

  if (!tc->root){
    /* First symbol */
    tc->root = t;
    tc->last = tc->root;

  } else {
    tc->last->next = t;
    t->prev = tc->last;
    tc->last = t;
  }
}


void tknstTknRead(
    int c,
    TokenContext *tc
){
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
    TokenContext *tc
){
  Token *t = tc->last;
  t->value[t->len] = '\0';
  t->type = tc->state - tc->states;
}


struct tokenState *tknstNumrNext(
    int c,
    TokenContext *tc
){
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
    TokenContext *tc
){
  Token *t = tc->last;
  t->value[t->len] = '\0';
  t->type = tc->state - tc->states;
}


struct tokenState *tknstSymbNext(
    int c,
    TokenContext *tc
){
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
    TokenContext *tc
){
  tknstTknEnter(tc);

  tc->last->data = OPER_NONE;
}


void tknstOperExit(
    TokenContext *tc
){
  Token *t = tc->last;
  t->value[t->len] = '\0';
  t->type = tc->state - tc->states;
}


void tknstOperRead(
    int c,
    TokenContext *tc
){
  Token *t = tc->last;
  int splitOp = 1;

  switch (t->data){
  case OPER_NONE:
    /* Initial character of operator*/
    splitOp = 0;
    operatorInitState(c, t);
    break;

  case OPER_FSLS:
    /* / */
    switch (c){
    case '*': t->data = OPER_MCMT; splitOp=0; break;
    case '/': t->data = OPER_SCMT; splitOp=0; break;
    }
    break;

  case OPER_PLUS:
    /* + */
    if (c == '='){
      t->data = OPER_PLUS_EQ;
      splitOp = 0;
    }
  }

  if (splitOp){
    /* If operator doesn't chain, then start new one */
    tknstOperExit(tc);
    tknstOperEnter(tc);
    operatorInitState(c, tc->last);
  }

  tknstTknRead(c, tc);
}


struct tokenState *tknstOperNext(
    int c,
    TokenContext *tc
){
  int tData = tc->last->data;
  if (tData == OPER_MCMT){
    return tc->states + TKNST_MCMT;
  } else if (tData == OPER_SCMT) {
    return tc->states + TKNST_SCMT;
  }

  if (isspace(c)){
    return tc->states + TKNST_INTR;

  } else if (isalpha(c)){
    return tc->states + TKNST_SYMB;

  } else if (isdigit(c)){
    return tc->states + TKNST_NUMR;
  }

  return tc->states + TKNST_OPER;
}


/* Comment state */
void tknstCmtEnter(
    TokenContext *tc
){
  tc->states[TKNST_MCMT].data = CMT_START;
  tc->states[TKNST_SCMT].data = CMT_START;
  rewindToken(tc);
}


void tknstMCmtRead(
    int c,
    TokenContext *tc
){
  switch (tc->state->data){
  case CMT_START:
  case CMT_TEXT:
    if (c == '*'){
      tc->state->data = CMT_STAR;
    } else {
      tc->state->data = CMT_TEXT;
    }
    break;

  case CMT_STAR:
    if (c == '/'){
      tc->state->data = CMT_DONE;
    } else if (c != '*'){
      tc->state->data = CMT_TEXT;
    }
  }
}


void tknstSCmtRead(
    int c,
    TokenContext *tc
){
  if (c == '\n'){
    tc->state->data = CMT_DONE;
  }
}


/** Token state switch callback for comments */
struct tokenState *tknstCmtNext(
    int c,
    TokenContext *tc
){
  if (tc->state->data == CMT_DONE){
    //return tc->states + TKNST_INTR;
    return tknstIntrNext(c, tc);
  } else {
    return tc->state;
  }
}

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


void operatorInitState(
    int c,
    Token *t
){
  switch (c){
  case '!': t->data = OPER_EXCL; break;
  case '$': t->data = OPER_SYS; break;
  case '%': t->data = OPER_MOD; break;
  case '&': t->data = OPER_AMP; break;
  case '(': t->data = OPER_OPRN; break;
  case ')': t->data = OPER_CPRN; break;
  case '*': t->data = OPER_STAR; break;
  case '+': t->data = OPER_PLUS; break;
  case '/': t->data = OPER_FSLS; break;
  case ';': t->data = OPER_SCLN; break;
  case '<': t->data = OPER_LT; break;
  case '=': t->data = OPER_EQ; break;
  case '>': t->data = OPER_GT; break;
  case '{': t->data = OPER_OCRL; break;
  case '}': t->data = OPER_CCRL; break;
  default:
    printf("Unknown operator: %c\n", c);
  }
}


void rewindToken(
    TokenContext *tc
){
  Token *t = tc->last;
  if (tc->root == tc->last){
    /* Only one token exists */
    freeTokens(t);
    tc->root = NULL;
    tc->last = NULL;

  } else {
    /* Multiple tokens exist */
    tc->last = t->prev;

    freeTokens(t);
  }
}
