#pragma once
#include <CGSC/cgsc.h>

#ifdef _MSC_VER 
	#define strncasecmp _strnicmp
	#define strcasecmp _stricmp
#endif

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

/// <summary>
/// Trim a string.
/// </summary>
void GScr_Trim();

/// <summary>
/// Check if a string starts with a specific value.
/// </summary>
void GScr_StartsWith();

/// <summary>
/// Check if a string ends with a specific value.
/// </summary>
void GScr_EndsWith();

/// <summary>
/// Join string array with a separator.
/// </summary>
void GScr_StrJoin();

/// <summary>
/// Replace a string.
/// </summary>
void GScr_Replace();

/// <summary>
/// Join filepath strings.
/// </summary>
void GScr_PathJoin();
