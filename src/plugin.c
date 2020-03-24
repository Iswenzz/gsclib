#include "linq/gsclinq.h"
#include "collections/list.h"
#include "utility/utility.h"

#ifndef PLUGIN_INCLUDES
#include "../../pinc.h"
#endif

PCL int OnInit()
{
    // utility.h
    Plugin_ScrAddFunction("comPrintf", 	&GScr_ComPrintf);
	Plugin_ScrAddFunction("getType", 	&GScr_GetType);

    // gsclinq.h
	Plugin_ScrAddFunction("all", 		&GScr_LINQ_All);
	Plugin_ScrAddFunction("where", 		&GScr_LINQ_Where);
	Plugin_ScrAddFunction("any", 		&GScr_LINQ_Any);
	Plugin_ScrAddFunction("min", 		&GScr_LINQ_Min);
	Plugin_ScrAddFunction("max", 		&GScr_LINQ_Max);
	Plugin_ScrAddFunction("last",		&GScr_LINQ_Last);
	Plugin_ScrAddFunction("first", 		&GScr_LINQ_First);
	Plugin_ScrAddFunction("cast", 		&GScr_LINQ_Cast);
	Plugin_ScrAddFunction("oftype", 	&GScr_LINQ_OfType);
	Plugin_ScrAddFunction("sort", 		&GScr_LINQ_Sort);
	Plugin_ScrAddFunction("average", 	&GScr_LINQ_Average);
	Plugin_ScrAddFunction("count", 		&GScr_LINQ_Count);
	Plugin_ScrAddFunction("sum", 		&GScr_LINQ_Sum);
	Plugin_ScrAddFunction("select", 	&GScr_LINQ_Select);
	Plugin_ScrAddFunction("range", 		&GScr_LINQ_Range);
	Plugin_ScrAddFunction("repeat", 	&GScr_LINQ_Repeat);
	Plugin_ScrAddFunction("reverse", 	&GScr_LINQ_Reverse);

    // list.h
    Plugin_ScrAddFunction("listnew", 	&GScr_LIST_new);
	Plugin_ScrAddFunction("listadd", 	&GScr_LIST_add);
	Plugin_ScrAddFunction("listremove", &GScr_LIST_remove);
	Plugin_ScrAddFunction("listinsert", &GScr_LIST_insert);
	Plugin_ScrAddFunction("listlength", &GScr_LIST_length);
	Plugin_ScrAddFunction("listget", 	&GScr_LIST_get);

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
