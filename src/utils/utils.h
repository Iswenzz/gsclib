#pragma once
#include <cgsc.h>

/// <summary>
/// Print a formatted message to the console output.
/// </summary>
void GScr_ComPrint();

/// <summary>
/// Print a formatted message on a new line to the console output.
/// </summary>
void GScr_ComPrintLn();

/// <summary>
/// Print a formatted message.
/// </summary>
/// <param name="newLine">Should add a new line at the end.</param>
/// <param name="print">The function used for printing.</param>
void Scr_PrintF(qboolean newLine, void (*print)(const char *, ...));

/// <summary>
/// Get the time since epoch in milliseconds.
/// </summary>
void GScr_GetSysTime();

/// <summary>
/// Get the type name of a GSC variable.
/// </summary>
void GScr_GetType();

/// <summary>
/// Check the condition and return the 1st value if true or the second value if false.
/// </summary>
void GScr_Ternary();

/// <summary>
/// Give a default value if the variable is undefined.
/// </summary>
void GScr_IfUndef();

/// <summary>
/// Execute a system command.
/// </summary>
void GScr_System();
