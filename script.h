#ifndef SCRIPT_H
#define SCRIPT_H

#include "operation.h"
#include "cellparameters.h"

/* Script structure */
struct Scp{
	/* List of operations */
	struct Op* pOps;
	
	/* Operation count */
	GAIS_WORD cOps;
	
	/* Index of active operation */
	GAIS_WORD iOp;
	
	/* Script private memory */
	GAIS_WORD* pMem;
	
	/* Private memory size */
	GAIS_WORD cMem;
};

/* Script memory addressing structure:
	Memory addresses from 0 to cMem-1 are private memory. Everything beyond
	is cell public memory.
 */


/* Gets a script's active operation */
Op* getScpActOp(struct Scp* pScp);


#endif