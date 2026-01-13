#include "cgsc4.h"

#if CGSC_EQ(4)

void Scr_AddFunc(const char *codePosValue)
{
	IncInParam();
	IGScrVmPub.top->type = VAR_FUNCTION;
	IGScrVmPub.top->u.codePosValue = codePosValue;
}

#endif
