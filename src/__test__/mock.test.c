#include <stdarg.h>

/// <summary>
/// Print a message to the console.
/// </summary>
/// <param name="fmt">The format string.</param>
/// <param name="...">The format arguments.</param>
void Plugin_Printf(const char* fmt, ...)
{
    va_list argptr;
    va_start(argptr, fmt);
    printf(fmt, argptr);
    va_end(argptr);
}

/// <summary>
/// Gets a string from a GSC string index.
/// </summary>
/// <param name="index">The string index.</param>
/// <returns></returns>
const char* Plugin_SL_ConvertToString(int index) 
{ 
    return "string"; 
}
