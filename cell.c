#include "cell.h"

Scp* getCellActScp(struct Cell* pCell){
	/* Get index [modulus # of scripts], offset by script pointer address */
	return pCell->pScps + (pCell->iScp % pCell->cScps);
}