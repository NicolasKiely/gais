#ifdef CELL_H
#define CELL_H

#include "script.h"

/* Cell Structure */
struct Cell{
	/* List of scripts */
	Scp* pScp;
	
	/* Script count */
	Scp* cScp;
};


#endif