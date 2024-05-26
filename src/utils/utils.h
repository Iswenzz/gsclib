#pragma once
#include <CGSC/cgsc.h>

#define Q_COLOR_ESCAPE '^'
#define Q_IsColorString(p) (p && *(p) == Q_COLOR_ESCAPE && *((p) + 1) && *((p) + 1) != Q_COLOR_ESCAPE)

#define COLOR_BLACK '0'
#define COLOR_RED '1'
#define COLOR_GREEN '2'
#define COLOR_YELLOW '3'
#define COLOR_BLUE '4'
#define COLOR_CYAN '5'
#define COLOR_MAGENTA '6'
#define COLOR_WHITE '7'

#define ColorIndex(c) (((c) - '0') & 7)

extern int q3ToAnsi[8];

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
/// Format a string.
/// </summary>
/// <param name="format">The string to format.</param>
/// <param name="...">The format arguments.</param>
/// <returns>The formatted string.</returns>
char* fmt(char* format, ...);

/// <summary>
/// Check if a flag is set in the GSC array flag variable.
/// </summary>
/// <param name="var">GSC array flag variable.</param>
/// <param name="flag">The flag to test.</param>
/// <returns>The result of the test.</returns>
qboolean HasFlag(int var, int flag);

/// <summary>
/// Check if the specified flag is the only flag set in the GSC array flag variable.
/// </summary>
/// <param name="var">GSC array flag variable.</param>
/// <param name="flag">The flag to test.</param>
/// <returns>The result of the test.</returns>
qboolean IsFlag(int var, int flag);
