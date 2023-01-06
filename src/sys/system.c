#include "system.h"
#include "utils/utils.h"
#include "utils/vsnprintf.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

critical_sections sections = { 0 };
async_handler* asyncHandler = NULL;

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

void GScr_CriticalSection()
{
	CHECK_PARAMS(1, "Usage: CriticalSection(<name>)");

	const char* name = Plugin_Scr_GetString(0);
	for (int i = 0; i < sections.length; i++)
	{
		if (!strcmp(name, sections.list[i].id))
			return;
	}
	sections.list = !sections.list
		? (critical_section*)malloc(sizeof(critical_section))
		: (critical_section*)realloc(sections.list, (sections.length + 1) * sizeof(critical_section));
	
	critical_section* section = &sections.list[sections.length++];
	strcpy(section->id, name);
	section->locked = qfalse;
}

void GScr_EnterCriticalSection()
{
	CHECK_PARAMS(1, "Usage: EnterCriticalSection(<name>)");

	critical_section* section = NULL;
	const char* name = Plugin_Scr_GetString(0);

	for (int i = 0; i < sections.length; i++)
	{
		if (!strcmp(name, sections.list[i].id))
		{
			section = &sections.list[i];
			break;
		}
	}
	if (!section)
	{
		Plugin_Scr_Error(fmt("MutexAcquire(): section %s not found.", name));
		return;
	}
	if (!section->locked)
	{
		section->locked = qtrue;
		Plugin_Scr_AddBool(qtrue);
		return;
	}
	Plugin_Scr_AddBool(qfalse);
}

void GScr_LeaveCriticalSection()
{
	CHECK_PARAMS(1, "Usage: LeaveCriticalSection(<name>)");

	critical_section* section = NULL;
	const char* name = Plugin_Scr_GetString(0);

	for (int i = 0; i < sections.length; i++)
	{
		if (!strcmp(name, sections.list[i].id))
		{
			section = &sections.list[i];
			break;
		}
	}
	if (!section)
	{
		Plugin_Scr_Error(fmt("LeaveCriticalSection(): section %s not found.", name));
		return;
	}
	section->locked = qfalse;
}

void GScr_AsyncStatus()
{
	CHECK_PARAMS(1, "Usage: Async_Status(<request>)");

	async_worker** worker = (async_worker**)Plugin_Scr_GetInt(0);
	if (!worker || !(*worker))
	{
		Plugin_Scr_AddInt(0);
		return;
	}
	Plugin_Scr_AddInt((*worker)->status);
}

void GScr_IsWindows()
{
#ifdef _WIN32
	Plugin_Scr_AddBool(qtrue);
#else
	Plugin_Scr_AddBool(qfalse);
#endif
}

void GScr_IsLinux()
{
#ifdef _WIN32
	Plugin_Scr_AddBool(qfalse);
#else
	Plugin_Scr_AddBool(qtrue);
#endif
}

void GScr_CoD4X_Version()
{
	Plugin_Scr_AddFloat(Plugin_Sys_GetCommonVersion());
}

void GScr_GSCLIB_Version()
{
	char version[20] = { 0 };
	sprintf(version, "%d.%d", GSCLIB_VERSION_MAJOR, GSCLIB_VERSION_MINOR);
	Plugin_Scr_AddFloat(atof(version));
}

void GScr_CGSC_Version()
{
	Plugin_Scr_AddFloat(Plugin_CGSC_Version());
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
		Sys_AnsiColorPrint(fmt("%s%s", format, newLine ? "\n" : ""), print);
		return;
	}
	VariableValueArray args = Plugin_Scr_CreateArray(argCount - 1);

	for (int i = 1; i < argCount; i++)
		args.items[i - 1] = *Plugin_Scr_SelectParam(i);

	Scr_vsnprintf(buffer, sizeof(buffer), format, args);
	if (newLine) strcat(buffer, "\n");
	Sys_AnsiColorPrint(buffer, print);

	Plugin_Scr_FreeArray(&args);
}

void Sys_AnsiColorPrint(const char* msg, void (*print)(const char*, ...))
{
	int length = 0;
	static char buffer[MAXPRINTMSG] = { 0 };

	while (*msg)
	{
		if (Q_IsColorString(msg) || *msg == '\n')
		{
			if (length > 0)
			{
				buffer[length] = '\0';
				print(buffer);
				length = 0;
			}
			if (*msg == '\n')
			{
				print("\033[0m\n");
				msg++;
			}
			else
			{
				snprintf(buffer, sizeof(buffer), "\033[1;%dm", q3ToAnsi[ColorIndex(*(msg + 1))]);
				print(buffer);
				msg += 2;
			}
		}
		else
		{
			if (length >= MAXPRINTMSG - 1)
				break;
			buffer[length] = *msg;
			length++;
			msg++;
		}
	}
	if (length > 0)
	{
		buffer[length] = '\0';
		print(buffer);
	}
}

void ShutdownCriticalSections()
{
	if (sections.list)
	{
		free(sections.list);
		sections.list = NULL;
		sections.length = 0;
	}
}

void AsyncHandlerRestart()
{
	Plugin_AsyncShutdown(asyncHandler);
	asyncHandler = Plugin_AsyncInit();
}

void AsyncHandlerShutdown()
{
	Plugin_AsyncShutdown(asyncHandler);
}
