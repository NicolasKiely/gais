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

#endif