#ifndef CELL_H
#define CELL_H

#include "script.h"

/* Cell Structure */
struct Cell{
	/* List of scripts */
	Scp* pScps;
	
	/* Script count */
	Scp* cScps;
	
	/* Index of active script */
	GAIS_WORD iScp;
};


/* Returns pointer to a cell's active script */
Scp* getCellActScp(struct Cell* pCell);


#endif