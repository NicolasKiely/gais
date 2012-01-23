#ifndef CELLEXECUTER_H
#define CELLEXECUTER_H

#include "cell.h"

/* Runs a cell through a step
`	Steps:
	- Get current script to execute
	- Get current operation to execute
	- Execute operation
 */
void cellStep(struct Cell* pCell);


#endif