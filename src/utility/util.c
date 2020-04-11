#include "util.h"

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
