#include "utils.h"
#include "vsnprintf.h"

#include <cgsc.h>
#include <stdlib.h>

void GScr_Ternary()
{
	CHECK_PARAMS(3, "Usage: Ternary(<condition>, <var if true>, <var if false>)");

	qboolean condition = Plugin_Scr_GetInt(0);
	VariableValue *a = Plugin_Scr_SelectParam(1);
	VariableValue *b = Plugin_Scr_SelectParam(2);
	Plugin_Scr_AddVariable(condition ? a : b);
}

void GScr_IfUndef()
{
	CHECK_PARAMS(2, "Usage: IfUndef(<var>, <default if undef>)");

	VariableValue *a = Plugin_Scr_SelectParam(0);
	VariableValue *b = Plugin_Scr_SelectParam(1);
	Plugin_Scr_AddVariable(a->type == VAR_UNDEFINED ? b : a);
}

void GScr_ComPrintF()
{
	const int argCount = Plugin_Scr_GetNumParam();
	if (argCount < 1)
	{
		Plugin_Scr_Error("Usage: comPrintF(<fmt>, <?arguments...>)");
		return;
	}
	char buffer[MAX_STRING_CHARS];
	const char* format = Plugin_Scr_GetString(0);

	if (argCount == 1)
	{
		Plugin_Printf(format);
		return;
	}
	VariableValue* args = (VariableValue*)malloc((argCount - 1) * sizeof(VariableValue));

	for (int i = 1; i < argCount; i++)
		args[i - 1] = *Plugin_Scr_SelectParam(i);
	Scr_vsnprintf(buffer, sizeof(buffer), format, args);

	Plugin_Printf(buffer);
	free(args);
}

void GScr_ComPrintLn()
{
	const int argCount = Plugin_Scr_GetNumParam();
	if (argCount == 0)
	{
		Plugin_Printf("\n");
		return;
	}
	char buffer[MAX_STRING_CHARS];
	char* format = Plugin_Scr_GetString(0);

	if (argCount == 1)
	{
		Plugin_Printf(fmt("%s\n", format));
		return;
	}
	VariableValue* args = (VariableValue*)malloc((argCount - 1) * sizeof(VariableValue));

	for (int i = 1; i < argCount; i++)
		args[i - 1] = *Plugin_Scr_SelectParam(i);
	Scr_vsnprintf(buffer, sizeof(buffer), format, args);
	strcat(buffer, "\n");

	Plugin_Printf(buffer);
	free(args);
}

void GScr_GetSysTime()
{
	CHECK_PARAMS(0, "Usage: GetSysTime()");
	Plugin_Scr_AddInt(Plugin_Milliseconds());
}

void GScr_GetType()
{
	CHECK_PARAMS(1, "Usage: GetType(<var>)");

	VariableValue *var = Plugin_Scr_SelectParam(0);
	switch (var->type)
	{
		case VAR_POINTER:
			switch (Plugin_Scr_GetObjectType(var->u.pointerValue))
			{
				case VAR_ARRAY: 	Plugin_Scr_AddString("ARRAY"); 				break;
				case VAR_OBJECT:	Plugin_Scr_AddString("OBJECT"); 			break;
				case VAR_ENTITY:	Plugin_Scr_AddString("ENTITY"); 			break;
			}
			break;
		case VAR_UNDEFINED: 		Plugin_Scr_AddString("UNDEFINED"); 			break;
		case VAR_STRING: 			Plugin_Scr_AddString("STRING");  			break;
		case VAR_ISTRING: 			Plugin_Scr_AddString("ISTRING");  			break;
		case VAR_VECTOR: 			Plugin_Scr_AddString("VECTOR");  			break;
		case VAR_FLOAT: 			Plugin_Scr_AddString("FLOAT"); 				break;
		case VAR_INTEGER: 			Plugin_Scr_AddString("INTEGER");  			break;
		case VAR_CODEPOS: 			Plugin_Scr_AddString("CODEPOS"); 			break;
		case VAR_PRECODEPOS: 		Plugin_Scr_AddString("PRECODEPOS"); 		break;
		case VAR_FUNCTION: 			Plugin_Scr_AddString("FUNCTION"); 			break;
		case VAR_STACK: 			Plugin_Scr_AddString("STACK"); 				break;
		case VAR_ANIMATION: 		Plugin_Scr_AddString("ANIMATION"); 			break;
		case VAR_DEVELOPER_CODEPOS: Plugin_Scr_AddString("DEVELOPER_CODEPOS");  break;
		case VAR_INCLUDE_CODEPOS: 	Plugin_Scr_AddString("INCLUDE_CODEPOS");  	break;
		case VAR_THREAD: 			Plugin_Scr_AddString("THREAD"); 			break;
		case VAR_NOTIFY_THREAD: 	Plugin_Scr_AddString("NOTIFY_THREAD");  	break;
		case VAR_TIME_THREAD: 		Plugin_Scr_AddString("TIME_THREAD");  		break;
		case VAR_CHILD_THREAD: 		Plugin_Scr_AddString("CHILD_THREAD");  		break;
		case VAR_OBJECT: 			Plugin_Scr_AddString("OBJECT"); 			break;
		case VAR_DEAD_ENTITY: 		Plugin_Scr_AddString("DEAD_ENTITY"); 		break;
		case VAR_ENTITY: 			Plugin_Scr_AddString("ENTITY"); 			break;
		case VAR_ARRAY: 			Plugin_Scr_AddString("ARRAY"); 				break;
		case VAR_DEAD_THREAD: 		Plugin_Scr_AddString("DEAD_THREAD"); 		break;
		case VAR_COUNT: 			Plugin_Scr_AddString("COUNT"); 				break;
		case VAR_THREAD_LIST: 		Plugin_Scr_AddString("THREAD_LIST"); 		break;
		case VAR_ENDON_LIST: 		Plugin_Scr_AddString("ENDON_LIST");  		break;
	}
}
