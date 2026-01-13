#include "compatibility.h"

#include <stdarg.h>
#include <stdio.h>

float CGSC_Version()
{
	char version[20] = { 0 };
	sprintf(version, "%d.%d", PLUGIN_HANDLER_VERSION_MAJOR, PLUGIN_HANDLER_VERSION_MINOR);
	return atof(version);
}

qboolean CGSC_Unsupported(qboolean versionCondition)
{
	if (!versionCondition)
		return qfalse;

	Scr_Error("CGSC: This feature is unsupported in this version.");
	return qtrue;
}

qboolean CGSC_UnsupportedMessage(qboolean versionCondition, char *format, ...)
{
	if (!versionCondition)
		return qfalse;
	va_list argptr;

	va_start(argptr, format);
	Scr_Error(fmt(format, argptr));
	va_end(argptr);
	return qtrue;
}

qboolean CGSC_SupportIndexedString()
{
	return Sys_GetCommonVersion() >= 20.0f;
}
