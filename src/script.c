#include "script.h"


Op* getScpActOp(struct Scp* pScp){
	/* Get index operation (modulus count), offset by op array address */
	return pScp->pOps + (pScp->iOp % pScp->cOps);
}