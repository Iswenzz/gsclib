#include "convert.h"

#include <cgsc.h>
#include <stdlib.h>
#include <stdio.h>

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
			Plugin_Scr_AddString(fmt("(%f, %f, %f)", 
				var->u.vectorValue[0],
				var->u.vectorValue[1], 
				var->u.vectorValue[2]));
			break;
		case VAR_INTEGER:
			Plugin_Scr_AddString(fmt("%d", var->u.intValue));
			break;
		case VAR_FLOAT:
			Plugin_Scr_AddString(fmt("%f", var->u.floatValue));
			break;
		default:
			Plugin_Scr_AddUndefined();
	}
}
