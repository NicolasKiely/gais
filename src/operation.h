#ifndef OPERATION_H
#define OPERATION_H

#include "cellparameters.h"

/* Memory unit in gais' virtual machine */
#define GAIS_WORD char

/* Instruction masks for parameter definitions */
/* Instruction word bit structure: (w=wing,b=base,i=instruction)
	bbwi iiii
 */
/* Binary mask = 1100 0000, right shift by 6 */
#define OPBSMASK 0xC0
#define OPBSSHFT 6
/* Binary mask = 0010 0000, right shift by 5 */
#define OPWGMASK 0x20
#define OPWGSHFT 5
/* Binary mask = 0001 1111, no shifting */
#define OPINMASK 0x1f


/* Operation structure */
struct Op{
	/* Instruction */
	GAIS_WORD in;
	
	/* Base parameter */
	GAIS_WORD bs;
	
	/* Wing parameter */
	GAIS_WORD wg;
};


/* Parameter definitions for operations */
enum OpParDef{
	/* Variable [00]*/
	DEFVAR = 0,
	/* Pointer [01]*/
	DEFPTR = 1,
	/* Constant/Literal/Value  [10]*/
	DEFVAL = 2,
	/* Ignore operation [11]*/
	DEFIGN = 3
};

/* Applies mask and bit shifting to access instruction definitions */
GAIS_WORD getOpBsDef(GAIS_WORD in);
GAIS_WORD getOpWgDef(GAIS_WORD in);
GAIS_WORD getOpInDef(GAIS_WORD in);


#endif