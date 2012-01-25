#ifndef CELL_H
#define CELL_H

#include "script.h"

/* Cell Structure */
struct Cell{
	/* List of scripts */
	struct Scp* pScps;
	
	/* Script count */
	struct Scp* cScps;
	
	/* Index of active script */
	GAIS_WORD iScp;
	
	/* Cell public memory */
	GAIS_WORD* pMem;
	
	/* Cell memory size */
	GAIS_WORD cMem;
};


/* Returns pointer to a cell's active script */
Scp* getCellActScp(struct Cell* pCell);

/* Returns pointer to variable in a script's address space */ 
GAIS_WORD* refCellMem(struct Cell* pCell, GAIS_WORD iScp, GAIS_WORD iVar);


#endif