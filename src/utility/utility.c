#include "utility.h"

void ComPrintf()
{
	if (Plugin_Scr_GetNumParam() != 1)
	{
		Plugin_Scr_Error("Usage: comPrintf(<string>)");
		return;
	}
	Plugin_Printf(Plugin_Scr_GetString(0));
}

void GetType()
{
	if (Plugin_Scr_GetNumParam() != 1)
	{
		Plugin_Scr_Error("Usage: getType(<var>)");
		return;
	}
	VariableValue *var = Plugin_Scr_SelectParam(0);
	switch (var->type)
	{
		case VAR_UNDEFINED: 		Plugin_Scr_AddString("VAR_UNDEFINED"); 			break;
		case VAR_POINTER: 			Plugin_Scr_AddString("VAR_POINTER");  			break;
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

uint32_t GetFlagsFromGSCArray(VariableValue **array, int array_size)
{
	uint32_t flags = 0;
	for (int i = 0; i < array_size; i++)
	{
		switch (array[i]->type)
		{
			case VAR_UNDEFINED: 		flags |= FLAG_UNDEFINED; 		 break;
			case VAR_POINTER: 			flags |= FLAG_POINTER; 			 break;
			case VAR_STRING: 			flags |= FLAG_STRING; 			 break;
			case VAR_ISTRING: 			flags |= FLAG_ISTRING; 			 break;
			case VAR_VECTOR: 			flags |= FLAG_VECTOR; 			 break;
			case VAR_FLOAT: 			flags |= FLAG_FLOAT; 			 break;
			case VAR_INTEGER: 			flags |= FLAG_INTEGER; 			 break;
			case VAR_CODEPOS: 			flags |= FLAG_CODEPOS; 			 break;
			case VAR_PRECODEPOS: 		flags |= FLAG_PRECODEPOS; 		 break;
			case VAR_FUNCTION: 			flags |= FLAG_FUNCTION; 		 break;
			case VAR_STACK: 			flags |= FLAG_STACK; 			 break;
			case VAR_ANIMATION: 		flags |= FLAG_ANIMATION; 		 break;
			case VAR_DEVELOPER_CODEPOS: flags |= FLAG_DEVELOPER_CODEPOS; break;
			case VAR_INCLUDE_CODEPOS: 	flags |= FLAG_INCLUDE_CODEPOS; 	 break;
			case VAR_THREAD: 			flags |= FLAG_THREAD; 			 break;
			case VAR_NOTIFY_THREAD: 	flags |= FLAG_NOTIFY_THREAD; 	 break;
			case VAR_TIME_THREAD: 		flags |= FLAG_TIME_THREAD; 		 break;
			case VAR_CHILD_THREAD: 		flags |= FLAG_CHILD_THREAD; 	 break;
			case VAR_OBJECT: 			flags |= FLAG_OBJECT; 			 break;
			case VAR_DEAD_ENTITY: 		flags |= FLAG_DEAD_ENTITY; 		 break;
			case VAR_ENTITY: 			flags |= FLAG_ENTITY; 			 break;
			case VAR_ARRAY: 			flags |= FLAG_ARRAY; 			 break;
			case VAR_DEAD_THREAD: 		flags |= FLAG_DEAD_THREAD; 		 break;
			case VAR_COUNT: 			flags |= FLAG_COUNT; 			 break;
			case VAR_THREAD_LIST: 		flags |= FLAG_THREAD_LIST; 		 break;
			case VAR_ENDON_LIST: 		flags |= FLAG_ENDON_LIST; 		 break;
		}
	}
	return flags;
}

qboolean HasFlag(int var, int flag)
{
	return (var & flag) == flag;
}

qboolean IsFlag(int var, int flag)
{
	return var == flag;
}