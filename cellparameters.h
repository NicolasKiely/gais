#ifndef CELLPARAMETERS_H
#define CELL_PARAMETERS_H

/* Data word size used in the gais VM */
#define GAIS_WORD char

/* Parameters for initializing a cell */
struct ClPar{
	/* [Maximum|Initial] number of operations per script */
	GAIS_WORD mOp;
}

#endif