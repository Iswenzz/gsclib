#pragma once
#include "CGSC/cgsc.h"

// clang-format off
#if CGSC_EQ(4)
	#ifdef COD4X
		#include <cscr_variable.h>
		#include <cscr_stringlist.h>
	#endif

	extern struct scrVarGlob_t gScrVarGlob;
	extern unsigned int Scr_AllocString(const char *s);
	extern void Scr_AddIString(const char *value);
	extern void Scr_AddArrayStringIndexed(unsigned int stringValue);
	extern VariableValue Scr_GetArrayIndexValue(unsigned int name);
	extern void IncInParam();

	#define IGScrVmPub gScrVmPub
	#define IGScrVmGlob gScrVmGlob
	#define IGScrVarGlob gScrVarGlob.variableList
#endif
// clang-format on
