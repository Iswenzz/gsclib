#include "utils.h"

#include <stdarg.h>

char *fmt(char *format, ...)
{
	va_list argptr;
	static char string[2][32000]; // In case va is called by nested functions
	static int index = 0;
	char *buf;

	buf = string[index & 1];
	index++;

	va_start(argptr, format);
	vsnprintf(buf, sizeof(*string), format, argptr);
	va_end(argptr);

	return buf;
}

qboolean HasFlag(int var, int flag)
{
	return (var & flag) == flag;
}

qboolean IsFlag(int var, int flag)
{
	return var == flag;
}
