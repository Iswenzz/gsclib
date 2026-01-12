#pragma once
#include "CGSC/cgsc.h"

EXPORT(float, Sys_GetCommonVersion());
EXPORT(float, CGSC_Version());
EXPORT(qboolean, CGSC_Unsupported(qboolean versionCondition));
EXPORT(qboolean, CGSC_UnsupportedMessage(qboolean versionCondition, char *format, ...));
EXPORT(qboolean, CGSC_SupportIndexedString());
