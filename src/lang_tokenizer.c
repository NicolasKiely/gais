#include <stdlib.h>

#include "lang_tokenizer.h"


Token *tokenizeStream(
    FILE *fin
){
  Token *token = NULL;

  return token;
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
