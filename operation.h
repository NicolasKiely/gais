#ifndef OPERATION_H
#define OPERATION_H

#define GAIS_WORD byte

struct op{
	/* Instruction */
	GAIS_WORD inst;
	
	/* Base parameter */
	GAIS_WORD basePrm;
	
	/* Wing parameter */
	GAIS_WORD wingPrm;
};

#endif