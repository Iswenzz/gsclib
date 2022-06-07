#include "stringutils.h"
#include "vsnprintf.h"

#include <cgsc.h>
#include <cwalk.h>
#include <ctype.h>
#include <stdlib.h>

#include "sys/system.h"

void GScr_IsStringAlpha()
{
	CHECK_PARAMS(1, "Usage: IsStringAlpha(<string>)");

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
	CHECK_PARAMS(1, "Usage: IsStringFloat(<string>)");

	const char *nptr = Plugin_Scr_GetString(0);
	char *endptr = NULL;
	strtof(nptr, &endptr);
	Plugin_Scr_AddBool(*endptr == '\0');
}

void GScr_IsStringInt()
{
	CHECK_PARAMS(1, "Usage: IsStringInt(<string>)");

	const char *nptr = Plugin_Scr_GetString(0);
	char *endptr = NULL;
	strtol(nptr, &endptr, 10);
	Plugin_Scr_AddBool(*endptr == '\0');
}

void GScr_ToUpper()
{
	CHECK_PARAMS(1, "Usage: ToUpper(<string>)");

	char *str = Plugin_Scr_GetString(0);
	char buffer[strlen(str) + 1];
	
	for (int i = 0; i < strlen(str); i++)
		buffer[i] = toupper(str[i]);
	buffer[sizeof(buffer) - 1] = '\0';
	Plugin_Scr_AddString(buffer);
}

void GScr_IsNullOrEmpty()
{
	CHECK_PARAMS(1, "Usage: IsNullOrEmpty(<string>)");

	VariableValue* var = Plugin_Scr_SelectParam(0);
	qboolean isString = var->type == VAR_STRING || var->type == VAR_ISTRING;

	Plugin_Scr_AddBool(!(isString && Plugin_SL_ConvertToString(var->u.stringValue)[0] != '\0'));
}

void GScr_ToRGB()
{
	CHECK_PARAMS(3, "Usage: ToRGB(<r>, <g>, <b>)");

	// Normalize vector for cod4 rgb
	vec3_t vec = { 0, 0, 0 };
	vec[0] = ((float)Plugin_Scr_GetInt(0)) / 255;
	vec[1] = ((float)Plugin_Scr_GetInt(1)) / 255;
	vec[2] = ((float)Plugin_Scr_GetInt(2)) / 255;

	Plugin_Scr_AddVector(vec);
}

void GScr_HexToRGB()
{
	CHECK_PARAMS(1, "Usage: HexToRGB(<hex string>)");

	char *string = Plugin_Scr_GetString(0);
    int rgb = 0;
    vec3_t vec = { 0, 0, 0 };

    if (string[0] == '#') 
		string++;
    if (strlen(string) != 6)
    {
        Plugin_Scr_ParamError(1, "Wrong HEX color input");
        return;
    }
    rgb = (int)strtol(string, NULL, 16);

    // Normalize vector for cod4 rgb
    vec[0] = ((float)((rgb >> 16) & 0xFF)) / 255;
    vec[1] = ((float)((rgb >> 8) & 0xFF)) / 255;
    vec[2] = ((float)(rgb & 0xFF)) / 255;
	Plugin_Scr_AddVector(vec);
}

void GScr_Fmt()
{
	const int argCount = Plugin_Scr_GetNumParam();
	if (argCount < 1)
	{
		Plugin_Scr_Error("Usage: fmt(<string>, <?arguments...>)");
		return;
	}
	char buffer[MAX_STRING_CHARS] = { 0 };
	const char* format = Plugin_Scr_GetString(0);
	
	if (argCount == 1)
	{
		Plugin_Scr_AddString(format);
		return;
	}
	VariableValue* args = (VariableValue*)malloc((argCount - 1) * sizeof(VariableValue));

	for (int i = 1; i < argCount; i++)
		args[i - 1] = *Plugin_Scr_SelectParam(i);
	Scr_vsnprintf(buffer, sizeof(buffer), format, args);

	Plugin_Scr_AddString(buffer);
	free(args);
}

void GScr_Trim()
{
	CHECK_PARAMS(1, "Usage: Trim(<string>)");

	char* ptr = NULL;
	char* string = Plugin_Scr_GetString(0);

	while (*string == ' ') 
		string++;

	ptr = string + strlen(string) - 1;
	while (*ptr == ' ') 
	{ 
		*ptr = '\0'; 
		ptr--; 
	}
	Plugin_Scr_AddString(string);
}

void GScr_StartsWith()
{
	CHECK_PARAMS(2, "Usage: StartsWith(<string>, <value>)");

	const char* string = Plugin_Scr_GetString(0);
	const char* value = Plugin_Scr_GetString(1);

	size_t stringLen = strlen(string);
	size_t valueLen = strlen(value);

	Plugin_Scr_AddBool(stringLen < valueLen ? qfalse : memcmp(value, string, valueLen) == 0);
}

void GScr_EndsWith()
{
	CHECK_PARAMS(2, "Usage: EndsWith(<string>, <value>)");

	const char* string = Plugin_Scr_GetString(0);
	const char* value = Plugin_Scr_GetString(1);

	size_t stringLen = strlen(string);
	size_t valueLen = strlen(value);

	Plugin_Scr_AddBool(stringLen >= valueLen && memcmp(string + stringLen - valueLen, value, valueLen) == 0);
}

void GScr_StrJoin()
{
	CHECK_PARAMS(2, "Usage: StrJoin(<array>, <separator>)");

	VariableValueArray* array = Plugin_Scr_GetArray(0);
	const char* separator = Plugin_Scr_GetString(1);

	char result[MAX_STRING_CHARS] = { 0 };
	uint32_t flags = Plugin_Scr_GetArrayFlags(array);

	if (IsFlag(flags, FLAG_STRING) || IsFlag(flags, FLAG_ISTRING))
	{
		for (int i = 0; i < array->length; i++)
		{
			const char* toJoin = Plugin_SL_ConvertToString(array->items[i]->u.stringValue);
			strcat(result, fmt("%s%s", toJoin, i == array->length - 1 ? "" : separator));
		}
	}
	Plugin_Scr_AddString(result);
}

void GScr_StrReplace()
{
	CHECK_PARAMS(3, "Usage: StrReplace(<source>, <search>, <replace>)");

	char source[MAX_STRING_CHARS] = { 0 };

	strcpy(source, Plugin_Scr_GetString(0));
	const char* search = Plugin_Scr_GetString(1);
	const char* replace = Plugin_Scr_GetString(2);

	char* p = NULL;
	if ((p = strstr(source, search)) == NULL)
	{
		Plugin_Scr_AddString(source);
		return;
	}
	int searchLen = strlen(search);
	int replaceLen = strlen(replace);
	int tailLen = strlen(p + searchLen);

	memmove(p + replaceLen, p + searchLen, tailLen + 1);
	memcpy(p, replace, replaceLen);

	Plugin_Scr_AddString(source);
}

void GScr_PathJoin()
{
	const int argCount = Plugin_Scr_GetNumParam();
	if (argCount < 2)
	{
		Plugin_Scr_Error("Usage: PathJoin(<paths...>)");
		return;
	}
	char buffer[MAX_STRING_CHARS] = { 0 };
	strcpy(buffer, Plugin_SL_ConvertToString(Plugin_Scr_SelectParam(0)->u.stringValue));

	for (int i = 1; i < argCount; i++)
	{
		int stringIndex = Plugin_Scr_SelectParam(i)->u.stringValue;
		const char* path = Plugin_SL_ConvertToString(stringIndex);
		cwk_path_join(buffer, path, buffer, sizeof(buffer));
	}
	Plugin_Scr_AddString(buffer);
}
