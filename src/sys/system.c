#include "system.h"
#include "utils/utils.h"
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

void GScr_GetIP(scr_entref_t num)
{
	client_t* cl = Plugin_GetClientForClientNum(num);

	if (!cl)
		Plugin_Scr_ObjectError("not a client\n");

	char ip[128];
	Plugin_NET_AdrToStringShortMT(&cl->netchan.remoteAddress, ip, sizeof(ip));
	Plugin_Scr_AddString(ip);
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
		Sys_AnsiColorPrint(fmt("%s%s", format, newLine ? "\n" : ""), print);
		return;
	}
	VariableValue* args = (VariableValue*)malloc((argCount - 1) * sizeof(VariableValue));

	for (int i = 1; i < argCount; i++)
		args[i - 1] = *Plugin_Scr_SelectParam(i);

	Scr_vsnprintf(buffer, sizeof(buffer), format, args);
	if (newLine) strcat(buffer, "\n");
	Sys_AnsiColorPrint(buffer, print);

	free(args);
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
				fputs(buffer, stderr);
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
