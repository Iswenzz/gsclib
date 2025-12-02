#pragma once
#include <CGSC/cgsc.h>

#define MAXPRINTMSG 1024

#define GSCLIB_VERSION_MAJOR 1
#define GSCLIB_VERSION_MINOR 5

typedef struct
{
	char id[60];
	qboolean locked;
} critical_section;

typedef struct
{
	critical_section* list;
	int length;
} critical_sections;

extern critical_sections sections;
extern async_handler* asyncHandler;

void GScr_System();
void GScr_SysPrint();
void GScr_SysPrintLn();
void GScr_GetSysTime();
void GScr_ComPrint();
void GScr_ComPrintLn();
void GScr_Exit();
void GScr_CriticalSection();
void GScr_CriticalSections();
void GScr_EnterCriticalSection();
void GScr_LeaveCriticalSection();
void GScr_AsyncStatus();
void GScr_IsWindows();
void GScr_IsLinux();
void GScr_CoD4X_Version();
void GScr_GSCLIB_Version();
void GScr_CGSC_Version();

void Sys_PrintF(const char* format, ...);
void Scr_PrintF(qboolean newLine, void (*print)(const char*, ...));
void Sys_AnsiColorPrint(const char* msg, void (*print)(const char*, ...));

void ShutdownCriticalSections();
void AsyncHandlerRestart();
void AsyncHandlerShutdown();
