#ifndef OPERATION_H
#define OPERATION_H

#include "cellparameters.h"

/* Memory unit in gais' virtual machine */
#define GAIS_WORD char

/* Operation structure */
struct Op{
	/* Instruction */
	GAIS_WORD in;
	
	/* Base parameter */
	GAIS_WORD bp;
	
	/* Wing parameter */
	GAIS_WORD wp;
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


#endif