#include "script.h"
#include "cell.h"

Scp* getCellActScp(struct Cell* pCell){
	/* Get index [modulus # of scripts], offset by script pointer address */
	return pCell->pScps + (pCell->iScp % pCell->cScps);
}


GAIS_WORD* refCellMem(struct Cell* pCell, GAIS_WORD iScp, GAIS_WORD iVar) {
	/* Get structure */
	struct Scp* pScp = pCell->pScp + (iScp % pCell->cScps);
	
  /* Check to see if accessing private or public memory */
  if (iVar < pScp->cMem) {
    /* Accessing private (script) memory */
    return pScp->pMem + iVar;
  } else {
    /* Accessing public (cell) memory */
    return pCell->pMem + (iVar - pScp->cMem);
  }

}