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
			break;
		case DEFPTR:
			break;
		case DEFVAL:
			tempVar = pOp->bs;
			pBs = @tempVar;
			break;
		case DEFIGN:
			break;
	}
	
	switch (wgDef) {
		case DEFVAR:
			break;
		case DEFPTR:
			break;
	}
}