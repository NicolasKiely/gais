#ifndef INSTRUCTIONSET_H
#define INSTRUCTIONSET_H

#include "cellparameters.h"

/* An instruction space, for script execution */
struct inSet{
	/* Array of functions [instructions] */
	void (**pFn)();
	
	/* Number of functions */
	GAIS_WORD cFn;
};

#endif