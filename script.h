#ifndef SCRIPT_H
#define SCRIPT_H

#include "operation.h"
#include "cellparameters.h"

/* Script structure */
struct Scp{
	/* List of operations */
	Op* pOps;
	
	/* Operation count */
	GAIS_WORD cOps;	
};


#endif