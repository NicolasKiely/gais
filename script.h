#ifndef SCRIPT_H
#define SCRIPT_H

#include "operation.h"
#include "cellparameters.h"

/* Script structure */
struct Scp{
	/* List of operations */
	Struct Op* pOps;
	
	/* Operation count */
	GAIS_WORD cOps;
	
	/* Index of active operation */
	GAIS_WORD iOp;
};


/* Gets a script's active operation */
Op* getScpActOp(struct Scp* pScp);


#endif