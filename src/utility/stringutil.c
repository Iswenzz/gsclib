#include "stringutil.h"
#include <cgsc.h>
#include <stdlib.h>
#include <ctype.h>

void GScr_IsStringAlpha()
{
	if (Plugin_Scr_GetNumParam() != 1)
	{
		Plugin_Scr_Error("Usage: IsStringAlpha(<string>)");
		return;
	}
	const char *str = Plugin_Scr_GetString(0);
	for (int i = 0; i < strlen(str); i++)
	{
		if (!isalpha(str[i]))
		{
			Plugin_Scr_AddBool(qfalse);
			return;
		}
	}
	Plugin_Scr_AddBool(qtrue);
}

void GScr_IsStringFloat()
{
	if (Plugin_Scr_GetNumParam() != 1)
	{
		Plugin_Scr_Error("Usage: IsStringFloat(<string>)");
		return;
	}
	const char *nptr = Plugin_Scr_GetString(0);
	char *endptr = NULL;
	strtof(nptr, &endptr);
	Plugin_Scr_AddBool(*endptr == '\0');
}

void GScr_IsStringInt()
{
	if (Plugin_Scr_GetNumParam() != 1)
	{
		Plugin_Scr_Error("Usage: IsStringInt(<string>)");
		return;
	}
	const char *nptr = Plugin_Scr_GetString(0);
	char *endptr = NULL;
	strtol(nptr, &endptr, 10);
	Plugin_Scr_AddBool(*endptr == '\0');
}

void GScr_ToUpper()
{
	if (Plugin_Scr_GetNumParam() != 1)
	{
		Plugin_Scr_Error("Usage: ToUpper(<string>)");
		return;
	}
	char *str = Plugin_Scr_GetString(0);
	char buffer[strlen(str) + 1];
	
	for (int i = 0; i < strlen(str); i++)
		buffer[i] = toupper(str[i]);
	buffer[sizeof(buffer) - 1] = '\0';
	Plugin_Scr_AddString(buffer);
}

void GScr_IsNullOrEmpty()
{
	if (Plugin_Scr_GetNumParam() != 1)
	{
		Plugin_Scr_Error("Usage: IsNullOrEmpty(<string>)");
		return;
	}
	VariableValue *var = Plugin_Scr_SelectParam(0);
	Plugin_Scr_AddBool(!((var->type == VAR_STRING || var->type  == VAR_ISTRING)
		&& Plugin_SL_ConvertToString(var->u.stringValue)[0] != '\0'));
}
