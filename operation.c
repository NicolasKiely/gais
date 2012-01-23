#include "operation.h"

GAIS_WORD getOpBsDef(GAIS_WORD in){
	return (in & OPBSMASK) >> OPBSSHFT;
}

GAIS_WORD getOpWgDef(GAIS_WORD in){
	return (in & OPWGMASK) >> OPWGSHFT;
}

GAIS_WORD getOpInDef(GAIS_WORD in){
	return in & OPINMASK;
}