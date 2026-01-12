#pragma once
#include "CGSC/cgsc.h"

#if CGSC(4)
	#ifdef PLUGIN
		#define CGSC_Printf(fmt, ...) Com_Printf(fmt, __VA_ARGS__);
	#else
		#define CGSC_Printf(fmt, ...) Com_Printf(0, fmt, __VA_ARGS__);
	#endif
#elif CGSC(3)
	#define CGSC_Printf(fmt, ...) Com_Printf(fmt, __VA_ARGS__);
#endif

#define GetRegisterValue(var, reg)   \
	register int _register asm(reg); \
	*var = _register;

char *fmt(char *format, ...);
qboolean HasFlag(int var, int flag);
qboolean IsFlag(int var, int flag);
