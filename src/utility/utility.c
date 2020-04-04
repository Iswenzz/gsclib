#include "utility.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
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

void GScr_ToInt()
{
	if (Plugin_Scr_GetNumParam() != 1)
	{
		Plugin_Scr_Error("Usage: ToInt(<type>)");
		return;
	}
	VariableValue *var = Plugin_Scr_SelectParam(0);
	switch (var->type)
	{
		case VAR_ISTRING:
		case VAR_STRING:
		{
			const char *nptr = Plugin_SL_ConvertToString(var->u.stringValue);
			char *endptr = NULL;
			long number = strtol(nptr, &endptr, 10);

			if (*endptr == '\0')
				Plugin_Scr_AddInt((int)number);
			break;
		}
		
		case VAR_VECTOR:
			Plugin_Scr_AddInt((int)(var->u.vectorValue[0] + var->u.vectorValue[1] + var->u.vectorValue[2]));
			break;
		case VAR_INTEGER:
			Plugin_Scr_AddInt(var->u.intValue);
			break;
		case VAR_FLOAT:
			Plugin_Scr_AddInt((int)var->u.floatValue);
			break;
		default:
			Plugin_Scr_AddUndefined();
	}
}

void GScr_ToFloat()
{
	if (Plugin_Scr_GetNumParam() != 1)
	{
		Plugin_Scr_Error("Usage: ToFloat(<type>)");
		return;
	}
	VariableValue *var = Plugin_Scr_SelectParam(0);
	switch (var->type)
	{
		case VAR_ISTRING:
		case VAR_STRING:
		{
			const char *nptr = Plugin_SL_ConvertToString(var->u.stringValue);
			char *endptr = NULL;
			float number = strtof(nptr, &endptr);

			if (*endptr == '\0')
				Plugin_Scr_AddFloat(number);
			break;
		}
		
		case VAR_VECTOR:
			Plugin_Scr_AddFloat(var->u.vectorValue[0] + var->u.vectorValue[1] + var->u.vectorValue[2]);
			break;
		case VAR_INTEGER:
			Plugin_Scr_AddFloat((float)var->u.intValue);
			break;
		case VAR_FLOAT:
			Plugin_Scr_AddFloat(var->u.floatValue);
			break;
		default:
			Plugin_Scr_AddUndefined();
	}
}

void GScr_ToString()
{
	if (Plugin_Scr_GetNumParam() != 1)
	{
		Plugin_Scr_Error("Usage: ToString(<type>)");
		return;
	}
	VariableValue *var = Plugin_Scr_SelectParam(0);
	switch (var->type)
	{
		case VAR_ISTRING:
		case VAR_STRING:
			Plugin_Scr_AddString(Plugin_SL_ConvertToString(var->u.stringValue));
			break;
		
		case VAR_VECTOR:
		{
			int cpyBufferSize = snprintf(NULL, 0, "(%f, %f, %f)", var->u.vectorValue[0],
				var->u.vectorValue[1], var->u.vectorValue[2]);
			char buffer[cpyBufferSize + 1];
			snprintf(buffer, cpyBufferSize + 1, "(%f, %f, %f)", var->u.vectorValue[0],
				var->u.vectorValue[1], var->u.vectorValue[2]);
			Plugin_Scr_AddString(buffer);
			break;
		}
		case VAR_INTEGER:
		{
			int cpyBufferSize = snprintf(NULL, 0, "%d", var->u.intValue);
			char buffer[cpyBufferSize + 1];
			snprintf(buffer, cpyBufferSize + 1, "%d", var->u.intValue);
			Plugin_Scr_AddString(buffer);
			break;
		}
		case VAR_FLOAT:
		{
			int cpyBufferSize = snprintf(NULL, 0, "%f", var->u.floatValue);
			char buffer[cpyBufferSize + 1];
			snprintf(buffer, cpyBufferSize + 1, "%f", var->u.floatValue);
			Plugin_Scr_AddString(buffer);
			break;
		}
		default:
			Plugin_Scr_AddUndefined();
	}
}

void GScr_Ternary()
{
	if (Plugin_Scr_GetNumParam() != 3)
	{
		Plugin_Scr_Error("Usage: Ternary(<condition>, <var if true>, <var if false>)");
		return;
	}
	qboolean condition = Plugin_Scr_GetInt(0);
	VariableValue *a = Plugin_Scr_SelectParam(1);
	VariableValue *b = Plugin_Scr_SelectParam(2);
	Plugin_Scr_AddVariable(condition ? a : b);
}

void GScr_IfUndef()
{
	if (Plugin_Scr_GetNumParam() != 2)
	{
		Plugin_Scr_Error("Usage: IfUndef(<var>, <default if undef>)");
		return;
	}
	VariableValue *a = Plugin_Scr_SelectParam(0);
	VariableValue *b = Plugin_Scr_SelectParam(1);
	Plugin_Scr_AddVariable(a->type == VAR_UNDEFINED ? b : a);
}

void GScr_ComPrintf()
{
	if (!Plugin_Scr_GetNumParam())
		Plugin_Printf("\n");
	else if (Plugin_Scr_GetNumParam() == 1)
		Plugin_Printf(Plugin_Scr_GetString(0));
	else
		Plugin_Scr_Error("Usage: ComPrintf(<message>)");
}

void GScr_GetType()
{
	if (Plugin_Scr_GetNumParam() != 1)
	{
		Plugin_Scr_Error("Usage: GetType(<var>)");
		return;
	}
	VariableValue *var = Plugin_Scr_SelectParam(0);
	switch (var->type)
	{
		case VAR_POINTER:
			switch (Plugin_Scr_GetObjectType(var->u.pointerValue))
			{
				case VAR_ARRAY: 	Plugin_Scr_AddString("VAR_ARRAY"); 				break;
				case VAR_OBJECT:	Plugin_Scr_AddString("VAR_OBJECT"); 			break;
				case VAR_ENTITY:	Plugin_Scr_AddString("VAR_ENTITY"); 			break;
			}
			break;
		case VAR_UNDEFINED: 		Plugin_Scr_AddString("VAR_UNDEFINED"); 			break;
		case VAR_STRING: 			Plugin_Scr_AddString("VAR_STRING");  			break;
		case VAR_ISTRING: 			Plugin_Scr_AddString("VAR_ISTRING");  			break;
		case VAR_VECTOR: 			Plugin_Scr_AddString("VAR_VECTOR");  			break;
		case VAR_FLOAT: 			Plugin_Scr_AddString("VAR_FLOAT"); 				break;
		case VAR_INTEGER: 			Plugin_Scr_AddString("VAR_INTEGER");  			break;
		case VAR_CODEPOS: 			Plugin_Scr_AddString("VAR_CODEPOS"); 			break;
		case VAR_PRECODEPOS: 		Plugin_Scr_AddString("VAR_PRECODEPOS"); 		break;
		case VAR_FUNCTION: 			Plugin_Scr_AddString("VAR_FUNCTION"); 			break;
		case VAR_STACK: 			Plugin_Scr_AddString("VAR_STACK"); 				break;
		case VAR_ANIMATION: 		Plugin_Scr_AddString("VAR_ANIMATION"); 			break;
		case VAR_DEVELOPER_CODEPOS: Plugin_Scr_AddString("VAR_DEVELOPER_CODEPOS");  break;
		case VAR_INCLUDE_CODEPOS: 	Plugin_Scr_AddString("VAR_INCLUDE_CODEPOS");  	break;
		case VAR_THREAD: 			Plugin_Scr_AddString("VAR_THREAD"); 			break;
		case VAR_NOTIFY_THREAD: 	Plugin_Scr_AddString("VAR_NOTIFY_THREAD");  	break;
		case VAR_TIME_THREAD: 		Plugin_Scr_AddString("VAR_TIME_THREAD");  		break;
		case VAR_CHILD_THREAD: 		Plugin_Scr_AddString("VAR_CHILD_THREAD");  		break;
		case VAR_OBJECT: 			Plugin_Scr_AddString("VAR_OBJECT"); 			break;
		case VAR_DEAD_ENTITY: 		Plugin_Scr_AddString("VAR_DEAD_ENTITY"); 		break;
		case VAR_ENTITY: 			Plugin_Scr_AddString("VAR_ENTITY"); 			break;
		case VAR_ARRAY: 			Plugin_Scr_AddString("VAR_ARRAY"); 				break;
		case VAR_DEAD_THREAD: 		Plugin_Scr_AddString("VAR_DEAD_THREAD"); 		break;
		case VAR_COUNT: 			Plugin_Scr_AddString("VAR_COUNT"); 				break;
		case VAR_THREAD_LIST: 		Plugin_Scr_AddString("VAR_THREAD_LIST"); 		break;
		case VAR_ENDON_LIST: 		Plugin_Scr_AddString("VAR_ENDON_LIST");  		break;
	}
}

qboolean HasFlag(int var, int flag)
{
	return (var & flag) == flag;
}

qboolean IsFlag(int var, int flag)
{
	return var == flag;
}

/**
 * Get the distance between two vec3_t.
 */
float vec_distance(vec3_t a, vec3_t b)
{
	float x = a[0] - b[0];
	float y = a[1] - b[1];
	float z = a[2] - b[2];

	return sqrtf((x * x) + (y * y) + (z * z));
}

/** 
 * qsort vec3_t comparison function.
 */ 
int vec3_cmp(const void *a, const void *b)
{
	vec3_t zero;
	vec3_t *vecA = (vec3_t *)a;
	vec3_t *vecB = (vec3_t *)b;

	float distanceA = vec_distance(*vecA, zero);
	float distanceB = vec_distance(*vecB, zero);
	
	return distanceA - distanceB; // float comparison: returns negative if b > a, and positive if a > b
}

/** 
 * qsort float comparison function.
 */ 
int float_cmp(const void *a, const void *b)
{
	const float *ia = (const float *)a;
	const float *ib = (const float *)b;
	return *ia - *ib; // float comparison: returns negative if b > a, and positive if a > b
}

/** 
 * qsort int comparison function.
 */ 
int int_cmp(const void *a, const void *b)
{
	const int *ia = (const int *)a;
	const int *ib = (const int *)b;
	return *ia - *ib; // integer comparison: returns negative if b > a, and positive if a > b
}

/** 
 * qsort C-string comparison function.
 */ 
int cstring_cmp(const void *a, const void *b)
{
	const char **ia = (const char **)a;
	const char **ib = (const char **)b;
	return strcmp(*ia, *ib);
}

/** 
 * qsort GSC variable vec3_t comparison function.
 */ 
int gsc_vec3_cmp(const void *a, const void *b)
{
	vec3_t zero;
	VariableValue *ia = *(VariableValue **)a;
	VariableValue *ib = *(VariableValue **)b;

	vec3_t vecA;
	vecA[0] = ia->u.vectorValue[0];
	vecA[1] = ia->u.vectorValue[1];
	vecA[2] = ia->u.vectorValue[2];

	vec3_t vecB;
	vecB[0] = ib->u.vectorValue[0];
	vecB[1] = ib->u.vectorValue[1];
	vecB[2] = ib->u.vectorValue[2];

	float distanceA = vec_distance(vecA, zero);
	float distanceB = vec_distance(vecB, zero);

	return distanceA - distanceB; // float comparison: returns negative if b > a, and positive if a > b
}

/** 
 * qsort GSC variable float comparison function.
 */ 
int gsc_float_cmp(const void *a, const void *b)
{
	VariableValue *ia = *(VariableValue **)a;
	VariableValue *ib = *(VariableValue **)b;
	return ia->u.floatValue - ib->u.floatValue; // float comparison: returns negative if b > a, and positive if a > b
}

/** 
 * qsort GSC variable int comparison function.
 */ 
int gsc_int_cmp(const void *a, const void *b)
{
	VariableValue *ia = *(VariableValue **)a;
	VariableValue *ib = *(VariableValue **)b;
	return ia->u.intValue - ib->u.intValue; // integer comparison: returns negative if b > a, and positive if a > b
}

/** 
 * qsort GSC variable C-string comparison function.
 */ 
int gsc_cstring_cmp(const void *a, const void *b)
{
	VariableValue *ia = *(VariableValue **)a;
	VariableValue *ib = *(VariableValue **)b;
	const char *sia = Plugin_SL_ConvertToString(ia->u.stringValue);
	const char *sib = Plugin_SL_ConvertToString(ib->u.stringValue);
	return strcmp(sia, sib);
}
