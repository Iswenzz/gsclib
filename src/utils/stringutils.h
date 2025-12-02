#pragma once
#include <CGSC/cgsc.h>

#ifdef _MSC_VER
	#define strncasecmp _strnicmp
	#define strcasecmp _stricmp
#endif

void GScr_IsNullOrEmpty();
void GScr_IsStringAlpha();
void GScr_IsStringInt();
void GScr_IsStringFloat();
void GScr_HexToRGB();
void GScr_ToRGB();
void GScr_Fmt();
void GScr_Trim();
void GScr_StartsWith();
void GScr_EndsWith();
void GScr_StrJoin();
void GScr_Replace();
void GScr_PathJoin();
