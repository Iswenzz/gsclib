#pragma once
#include <cgsc.h>

/// <summary>
/// Check if a string is undefined or empty.
/// </summary>
void GScr_IsNullOrEmpty();

/// <summary>
/// Check if a string is alphanumeric.
/// </summary>
void GScr_IsStringAlpha();

/// <summary>
/// Check if a string contains an integer.
/// </summary>
void GScr_IsStringInt();

/// <summary>
/// Check if a string contains a float.
/// </summary>
void GScr_IsStringFloat();

/// <summary>
/// Convert a string to upper case.
/// </summary>
void GScr_ToUpper();

/// <summary>
/// Convert a HEX color string to a normalized RGB vector.
/// </summary>
void GScr_HexToRGB();

/// <summary>
/// Normalize RGB vector.
/// </summary>
void GScr_ToRGB();

/// <summary>
/// Format a string.
/// </summary>
void GScr_Fmt();
