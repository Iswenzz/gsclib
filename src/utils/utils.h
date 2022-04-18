#pragma once
#include <cgsc.h>

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
