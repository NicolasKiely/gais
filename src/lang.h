/**
 * Header file for gais script language definition
 */

#ifndef _LANG_H_
#define _LANG_H_


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

/* Macro for building Keyword records */
#define KW_RECORD(NME) {KI_ ## NME, KW_ ## NME, KS_ ## NME, KS_ ## NME}

/* Flags for whether or not key word is supported */
#define KW_SUPPORTED       0
#define KW_NOT_SUPPORTED   1
#define KW_NOT_IMPLIMENTED 2

/* Flags for whether or not keyword designates type declaration */
#define KW_NOT_TYPE 0
#define KW_IS_TYPE 1

/* Key words (from ANSI C standard) */
#define KI_NON  0x00 // Not a keyword

#define KW_ASM  "asm"
#define KI_ASM  0x01
#define KS_ASM  KW_NOT_SUPPORTED
#define KT_ASM  KW_NOT_TYPE

#define KW_AUT  "auto"
#define KI_AUT  0x02
#define KS_AUT  KW_NOT_SUPPORTED
#define KT_AUT  KW_NOT_TYPE

#define KW_BRK  "break"
#define KI_BRK  0x03
#define KS_BRK  KW_NOT_IMPLIMENTED
#define KT_BRK  KW_NOT_TYPE

#define KW_CASE "case"
#define KI_CASE 0x04
#define KS_CASE KW_NOT_IMPLIMENTED
#define KT_CASE KW_NOT_TYPE

#define KW_CHAR "char"
#define KI_CHAR 0x05
#define KS_CHAR KW_NOT_IMPLIMENTED
#define KT_CHAR KW_IS_TYPE

#define KW_CNST "const"
#define KI_CNST 0x06
#define KS_CNST KW_NOT_SUPPORTED
#define KT_CNST KW_NOT_TYPE

#define KW_CONT "continue"
#define KI_CONT 0x07
#define KS_CONT KW_NOT_IMPLIMENTED
#define KT_CNST KW_NOT_TYPE

#define KW_DFLT "default"
#define KI_DFLT 0x08
#define KS_DFLT KW_NOT_IMPLIMENTED
#define KT_DFLT KW_NOT_TYPE

#define KW_DO   "do"
#define KI_DO   0x09
#define KS_DO   KW_NOT_IMPLIMENTED
#define KT_DO   KW_NOT_TYPE

#define KW_DBL  "double"
#define KI_DBL  0x0A
#define KS_DBL  KW_NOT_IMPLIMENTED
#define KT_DBL  KW_IS_TYPE

#define KW_ELSE "else"
#define KI_ELSE 0x0B
#define KS_ELSE KW_NOT_IMPLIMENTED
#define KT_ELSE KW_NOT_TYPE

#define KW_ENUM "enum"
#define KI_ENUM 0x0C
#define KS_ENUM KW_NOT_SUPPORTED
#define KT_ENUM KW_NOT_TYPE

#define KW_EXTN "extern"
#define KI_EXTN 0x0D
#define KS_EXTN KW_NOT_SUPPORTED
#define KT_EXTN KW_NOT_TYPE

#define KW_FLT  "float"
#define KI_FLT  0x0E
#define KS_FLT  KW_NOT_IMPLIMENTED
#define KT_FLT  KW_IS_TYPE

#define KW_FOR  "for"
#define KI_FOR  0x0F
#define KS_FOR  KW_NOT_IMPLIMENTED
#define KT_FOR  KW_NOT_TYPE

#define KW_GOTO "goto"
#define KI_GOTO 0x10
#define KS_GOTO KW_NOT_SUPPORTED
#define KT_GOTO KW_NOT_TYPE

#define KW_IF   "if"
#define KI_IF   0x11
#define KS_IF   KW_NOT_IMPLIMENTED
#define KT_IF   KW_NOT_TYPE

#define KW_INT  "int"
#define KI_INT  0x12
#define KS_INT  KW_NOT_IMPLIMENTED
#define KT_INT  KW_IS_TYPE

#define KW_LONG "long"
#define KI_LONG 0x13
#define KS_LONG KW_NOT_IMPLIMENTED
#define KT_LONG KW_IS_TYPE

#define KW_REG  "register"
#define KI_REG  0x14
#define KS_REG  KW_NOT_SUPPORTED
#define KT_REG  KW_NOT_TYPE

#define KW_RET  "return"
#define KI_RET  0x15
#define KS_RET  KW_NOT_IMPLIMENTED
#define KT_RET  KW_NOT_TYPE

#define KW_SHRT "short"
#define KI_SHRT 0x16
#define KS_SHRT KW_NOT_IMPLIMENTED
#define KT_SHRT KW_IS_TYPE

#define KW_SGN  "signed"
#define KI_SGN  0x17
#define KS_SGN  KW_NOT_IMPLIMENTED
#define KT_SGN  KW_IS_TYPE

#define KW_SZOF "sizeof"
#define KI_SZOF 0x18
#define KS_SZOF KW_NOT_IMPLIMENTED
#define KT_SZOF KW_NOT_TYPE

#define KW_STTC "static"
#define KI_STTC 0x19
#define KS_STTC KW_NOT_IMPLIMENTED
#define KT_STTC KW_IS_TYPE

#define KW_STRC "struct"
#define KI_STRC 0x1A
#define KS_STRC KW_NOT_IMPLIMENTED
#define KT_STRC KW_NOT_TYPE

#define KW_SWTC "switch"
#define KI_SWTC 0x1B
#define KS_SWTC KW_NOT_IMPLIMENTED
#define KT_SWTC KW_NOT_TYPE

#define KW_TPDF "typedef"
#define KI_TPDF 0x1C
#define KS_TPDF KW_NOT_SUPPORTED
#define KT_TPDF KW_NOT_TYPE

#define KW_UNN  "union"
#define KI_UNN  0x1D
#define KS_UNN  KW_NOT_SUPPORTED
#define KT_UNN  KW_NOT_TYPE

#define KW_USGN "unsigned"
#define KI_USGN 0x1E
#define KS_USGN KW_NOT_IMPLIMENTED
#define KT_USGN KW_IS_TYPE

#define KW_VOID "void"
#define KI_VOID 0x1F
#define KS_VOID KW_NOT_IMPLIMENTED
#define KT_VOID KW_IS_TYPE

#define KW_VLT  "volatile"
#define KI_VLT  0x20
#define KS_VLT  KW_NOT_SUPPORTED
#define KT_VLT  KW_NOT_TYPE

#define KW_WHL  "while"
#define KI_WHL  0x21
#define KS_WHL  KW_NOT_IMPLIMENTED
#define KT_WHL  KW_NOT_TYPE

#define KW_COUNT 0x21 // Number of keywords
#define KI_COUNT KW_COUNT


/* Key words structure array */
typedef struct keyWord {
  /* Keyword ID */
  int id;
  /* Keyword string */
  char *word;
  /* Support flag */
  int support;
  /* Whether or not keyword can be type declaration */
  int isType;
} KeyWord;
extern KeyWord KEY_WORDS[];


/**
 * Compares two keywords
 * Helper function for findKWID's bsearch lookup
 * @param a Pointer to first (alleged) key word
 * @param b Pointer to second key word
 * @return String comparison value of word strings
 */
int compKW(
    const void *a,
    const void *b
);

/**
 * Looks up id of reserved keyword
 * @param value String to lookup
 * @return 1+index of keyword, or 0 if not found
 */
int findKWID(
    char *value
);

#endif
