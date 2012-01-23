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
	GAIS_WORD bs = getOpBsDef(pOp->in);
	GAIS_WORD wg = getOpWgDef(pOp->in);
}