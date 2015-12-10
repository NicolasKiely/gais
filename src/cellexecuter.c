#include "operation.h"
#include "script.h"
#include "cell.h"
#include "cellexecuter.h"

void cellStep(struct Cell* pCell){
	if (pCell == null) {
		return;
	}

	/* Get active script */
	Struct Scp* pScp = getCellActScp(pCell);
	
	/* Get active operation */
	Struct Op* pOp = getScpActOp(pScp);
	
	/* Distribute Instruction masks */
	GAIS_WORD in = getOpInDef(pOp->in);
	GAIS_WORD bsDef = getOpBsDef(pOp->in);
	GAIS_WORD wgDef = getOpWgDef(pOp->in);
	
	/* Parameter pointers */
	GAIS_WORD* pBs;
	GAIS_WORD* pWg;
	/* Temporary variable in case Base parameter is a literal. */
	GAIS_WORD tempVar;
	
	/* Figure out parameters */
	switch (bsDef) {
		case DEFVAR:
      /* Reference variable */
      pBs = refCellMem(pCell, pCell->iScp, pOp->bs);
			break;
      
		case DEFPTR:
      /* Reference pointer */
      GAIS_WORD tempIRef = @refCellMem(pCell, pCell->iScp, pOp->bs);
      pBs = refCellMem(pCell, pCell->iScp, tempIRef);
			break;
      
		case DEFVAL:
      /* Reference as value. Since we're using pointers, we need to use
          to use some kind of temporary store to reference.
       */
			tempVar = pOp->bs;
			pBs = @tempVar;
			break;
      
		case DEFIGN:
      /* ??? */
			break;
	}
	
  /* Same as above */
	switch (wgDef) {
		case DEFVAR:
      pWg = refCellMem(pCell, pCell->iScp, pOp->wg);
			break;
      
		case DEFPTR:
      GAIS_WORD tempIRef = @refCellMem(pCell, pCell->iScp, pOp->wg);
      pBs = refCellMem(pCell, pCell->iScp, tempIRef);
			break;
	}
}