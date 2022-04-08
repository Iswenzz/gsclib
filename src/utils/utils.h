#pragma once

/// <summary>
/// Print a formatted message to the console output.
/// </summary>
void GScr_ComPrintF();

/// <summary>
/// Print a formatted message on a new line to the console output.
/// </summary>
void GScr_ComPrintLn();

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
