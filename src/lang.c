#include <stdlib.h>
#include <string.h>
#include "lang.h"

/** Keyword definition */
KeyWord KEY_WORDS[] = {
  KW_RECORD(ASM),
  KW_RECORD(AUT),
  KW_RECORD(BRK),
  KW_RECORD(CASE),
  KW_RECORD(CHAR),
  KW_RECORD(CNST),
  KW_RECORD(CONT),
  KW_RECORD(DFLT),
  KW_RECORD(DO),
  KW_RECORD(DBL),
  KW_RECORD(ELSE),
  KW_RECORD(ENUM),
  KW_RECORD(EXTN),
  KW_RECORD(FLT),
  KW_RECORD(FOR),
  KW_RECORD(GOTO),
  KW_RECORD(IF),
  KW_RECORD(INT),
  KW_RECORD(LONG),
  KW_RECORD(REG),
  KW_RECORD(RET),
  KW_RECORD(SHRT),
  KW_RECORD(SGN),
  KW_RECORD(SZOF),
  KW_RECORD(STTC),
  KW_RECORD(STRC),
  KW_RECORD(SWTC),
  KW_RECORD(TPDF),
  KW_RECORD(UNN),
  KW_RECORD(USGN),
  KW_RECORD(VOID),
  KW_RECORD(VLT),
  KW_RECORD(WHL)
};


int compKW(
    const void *a,
    const void *b
){
  KeyWord *wa = (KeyWord *) a;
  KeyWord *wb = (KeyWord *) b;
  return strcmp(wa->word, wb->word);
}


int findKWID(
    char *value
){
  KeyWord w = {.word=value};
  KeyWord *res = bsearch(&w, KEY_WORDS, KI_COUNT, sizeof(KeyWord), compKW);
  if (res == NULL){
    return 0;
  } else {
    return 1 + (res - KEY_WORDS);
  }
}
