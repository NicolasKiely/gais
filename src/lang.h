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


/* Key words (from ANSI C standard) */
#define KI_NON  0x00 // Not a keyword
#define KI_ASM  0x01 // Asm - not supported
#define KI_AUT  0x02 // Auto - not supported
#define KI_BRK  0x03 // Break
#define KI_CASE 0x04 // Case
#define KI_CHAR 0x05 // Char
#define KI_CNST 0x06 // const - not supported
#define KI_CONT 0x07 // Continue
#define KI_DFLT 0x08 // Default
#define KI_DO   0x09 // Do
#define KI_DBL  0x0A // Double
#define KI_ELSE 0x0B // Else
#define KI_ENUM 0x0C // Enum - not supported
#define KI_EXTN 0x0D // extern - not supported
#define KI_FLT  0x0E // Float
#define KI_FOR  0x0F // For
#define KI_GOTO 0x10 // Goto - not supported
#define KI_IF   0x11 // If
#define KI_INT  0x12 // Int
#define KI_LONG 0x13 // Long
#define KI_REG  0x14 // Register - not supported
#define KI_RET  0x15 // Return
#define KI_SHRT 0x16 // Short
#define KI_SGN  0x17 // Signed
#define KI_SZOF 0x18 // Sizeof
#define KI_STTC 0x19 // Static
#define KI_STRC 0x1A // Struct
#define KI_SWTC 0x1B // Switch
#define KI_TPDF 0x1C // Typedef - not supported
#define KI_UNN  0x1D // Union - not supported
#define KI_USGN 0x1E // Unsigned
#define KI_VOID 0x1F // Void
#define KI_VLT  0x20 // Volatile - not supported
#define KI_WHL  0x21 // While
#define KI_COUNT 0x21 // Number of keywords


/* Key words structure array */
typedef struct keyWord {
  char *word;
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
