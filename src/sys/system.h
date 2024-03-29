#pragma once
#include <CGSC/cgsc.h>

#define MAXPRINTMSG 1024

#define GSCLIB_VERSION_MAJOR 1
#define GSCLIB_VERSION_MINOR 5

/// <summary>
/// Critical section/mutex struct.
/// </summary>
typedef struct
{
	char id[60];
	qboolean locked;
} critical_section;

/// <summary>
/// Critical sections pool.
/// </summary>
typedef struct
{
	critical_section* list;
	int length;
} critical_sections;

extern critical_sections sections;
extern async_handler* asyncHandler;

/// <summary>
/// Execute a system command.
/// </summary>
void GScr_System();

/// <summary>
/// Print a formatted message to the system output.
/// </summary>
void GScr_SysPrint();

/// <summary>
/// Print a formatted message on a new line to the system output.
/// </summary>
void GScr_SysPrintLn();

/// <summary>
/// Get the time since epoch in milliseconds.
/// </summary>
void GScr_GetSysTime();

/// <summary>
/// Print a formatted message to the console output.
/// </summary>
void GScr_ComPrint();

/// <summary>
/// Print a formatted message on a new line to the console output.
/// </summary>
void GScr_ComPrintLn();

/// <summary>
/// Exit the program.
/// </summary>
void GScr_Exit();

/// <summary>
/// Create a critical section.
/// </summary>
void GScr_CriticalSection();

/// <summary>
/// Get the critical sections.
/// </summary>
void GScr_CriticalSections();

/// <summary>
/// Enter the critical section.
/// </summary>
void GScr_EnterCriticalSection();

/// <summary>
/// Leave the critical section.
/// </summary>
void GScr_LeaveCriticalSection();

/// <summary>
/// Get the async request status.
/// </summary>
void GScr_AsyncStatus();

/// <summary>
/// Is windows.
/// </summary>
void GScr_IsWindows();

/// <summary>
/// Is linux.
/// </summary>
void GScr_IsLinux();

/// <summary>
/// Get the CoD4x version.
/// </summary>
void GScr_CoD4X_Version();

/// <summary>
/// Get the gsclib version.
/// </summary>
void GScr_GSCLIB_Version();

/// <summary>
/// Get the CGSC version.
/// </summary>
void GScr_CGSC_Version();

/// <summary>
/// Print to stderr.
/// </summary>
/// <param name="format">The string format.</param>
/// <param name="...">The string format arguments.</param>
void Sys_PrintF(const char* format, ...);

/// <summary>
/// Print a formatted message.
/// </summary>
/// <param name="newLine">Should add a new line at the end.</param>
/// <param name="print">The function used for printing.</param>
void Scr_PrintF(qboolean newLine, void (*print)(const char*, ...));

/// <summary>
/// Transform Q3 colour codes to ANSI escape sequences.
/// </summary>
/// <param name="msg">The message to transform.</param>
/// <param name="print">The function used for printing.</param>
void Sys_AnsiColorPrint(const char* msg, void (*print)(const char*, ...));

/// <summary>
/// Shutdown the critical sections.
/// </summary>
void ShutdownCriticalSections();

/// <summary>
/// Restart the async handler.
/// </summary>
void AsyncHandlerRestart();

/// <summary>
/// Shutdown the async handler.
/// </summary>
void AsyncHandlerShutdown();
