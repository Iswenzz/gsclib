#include "linq/gsclinq.h"
#include "utility/utility.h"

#ifndef PLUGIN_INCLUDES
#include "../../pinc.h"
#endif

PCL int OnInit()
{
    // utility.h
    Plugin_ScrAddFunction("comprintf", 		&GScr_ComPrintf);
	Plugin_ScrAddFunction("gettype", 		&GScr_GetType);
	Plugin_ScrAddFunction("ternary", 		&GScr_Ternary);
	Plugin_ScrAddFunction("ifundef", 		&GScr_IfUndef);
	Plugin_ScrAddFunction("isnullorempty",	&GScr_IsNullOrEmpty);
	Plugin_ScrAddFunction("tostring", 		&GScr_ToString);
	Plugin_ScrAddFunction("toint", 			&GScr_ToInt);
	Plugin_ScrAddFunction("tofloat", 		&GScr_ToFloat);
	Plugin_ScrAddFunction("toupper", 		&GScr_ToUpper);
	Plugin_ScrAddFunction("isstringalpha", 	&GScr_IsStringAlpha);
	Plugin_ScrAddFunction("isstringfloat", 	&GScr_IsStringFloat);
	Plugin_ScrAddFunction("isstringint", 	&GScr_IsStringInt);

    // gsclinq.h
	Plugin_ScrAddFunction("all", 			&GScr_LINQ_All);
	Plugin_ScrAddFunction("where", 			&GScr_LINQ_Where);
	Plugin_ScrAddFunction("any", 			&GScr_LINQ_Any);
	Plugin_ScrAddFunction("min", 			&GScr_LINQ_Min);
	Plugin_ScrAddFunction("max", 			&GScr_LINQ_Max);
	Plugin_ScrAddFunction("last",			&GScr_LINQ_Last);
	Plugin_ScrAddFunction("first", 			&GScr_LINQ_First);
	Plugin_ScrAddFunction("cast", 			&GScr_LINQ_Cast);
	Plugin_ScrAddFunction("oftype", 		&GScr_LINQ_OfType);
	Plugin_ScrAddFunction("sort", 			&GScr_LINQ_Sort);
	Plugin_ScrAddFunction("average",		&GScr_LINQ_Average);
	Plugin_ScrAddFunction("count", 			&GScr_LINQ_Count);
	Plugin_ScrAddFunction("sum", 			&GScr_LINQ_Sum);
	Plugin_ScrAddFunction("select", 		&GScr_LINQ_Select);
	Plugin_ScrAddFunction("range",			&GScr_LINQ_Range);
	Plugin_ScrAddFunction("repeat",			&GScr_LINQ_Repeat);
	Plugin_ScrAddFunction("reverse", 		&GScr_LINQ_Reverse);

	return 0;
}

// Function used to obtain information about the plugin
// Memory pointed by info is allocated by the server binary
PCL void OnInfoRequest(pluginInfo_t *info)
{ 
	// =====  MANDATORY FIELDS  =====
	info->handlerVersion.major = PLUGIN_HANDLER_VERSION_MAJOR;
	info->handlerVersion.minor = PLUGIN_HANDLER_VERSION_MINOR; // Requested handler version

	// =====  OPTIONAL  FIELDS  =====
	info->pluginVersion.major = 1;
	info->pluginVersion.minor = 0;
	strncpy(info->fullName, "gsclib", sizeof(info->fullName));
	strncpy(info->shortDescription, "", sizeof(info->shortDescription));
	strncpy(info->longDescription, "", sizeof(info->longDescription));
}
