#include "system.h"
#include "utils/vsnprintf.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

void GScr_System()
{
	CHECK_PARAMS(1, "Usage: System(<command>)");
	Plugin_Scr_AddInt(system(Plugin_Scr_GetString(0)));
}

void GScr_GetSysTime()
{
	CHECK_PARAMS(0, "Usage: GetSysTime()");
	Plugin_Scr_AddInt(Plugin_Milliseconds());
}

void GScr_Exit()
{
	CHECK_PARAMS(1, "Usage: Exit(<code>)");
	exit(Plugin_Scr_GetInt(0));
}

void GScr_ComPrint()
{
	Scr_PrintF(qfalse, &Plugin_Printf);
}

void GScr_ComPrintLn()
{
	Scr_PrintF(qtrue, &Plugin_Printf);
}

void GScr_SysPrint()
{
	Scr_PrintF(qfalse, &Sys_PrintF);
}

void GScr_SysPrintLn()
{
	Scr_PrintF(qtrue, &Sys_PrintF);
}

void Sys_PrintF(const char* format, ...)
{
	va_list argptr;
	va_start(argptr, format);
	fprintf(stderr, format, argptr);
	va_end(argptr);
}

void Scr_PrintF(qboolean newLine, void (*print)(const char*, ...))
{
	const int argCount = Plugin_Scr_GetNumParam();
	if (argCount == 0)
	{
		print(newLine ? "\n" : "");
		return;
	}
	char buffer[MAX_STRING_CHARS] = { 0 };
	char* format = Plugin_Scr_GetString(0);

	if (argCount == 1)
	{
		print(fmt("%s%s", format, newLine ? "\n" : ""));
		return;
	}
	VariableValue* args = (VariableValue*)malloc((argCount - 1) * sizeof(VariableValue));

	for (int i = 1; i < argCount; i++)
		args[i - 1] = *Plugin_Scr_SelectParam(i);

	Scr_vsnprintf(buffer, sizeof(buffer), format, args);
	if (newLine) strcat(buffer, "\n");

	print(buffer);
	free(args);
}
