#include "linq/gsclinq.h"
#include "collections/list.h"
#include "utility/utility.h"

#ifndef PLUGIN_INCLUDES
#include "../../pinc.h"
#endif

PCL int OnInit()
{
    // utility.h
    Plugin_ScrAddFunction("comPrintf", 	&ComPrintf);
	Plugin_ScrAddFunction("getType", 	&GetType);

    // gsclinq.h
	Plugin_ScrAddFunction("all", 		&LINQ_All);
	Plugin_ScrAddFunction("where", 		&LINQ_Where);
	Plugin_ScrAddFunction("any", 		&LINQ_Any);
	Plugin_ScrAddFunction("min", 		&LINQ_Min);
	Plugin_ScrAddFunction("max", 		&LINQ_Max);
	Plugin_ScrAddFunction("last",		&LINQ_Last);
	Plugin_ScrAddFunction("first", 		&LINQ_First);
	Plugin_ScrAddFunction("cast", 		&LINQ_Cast);
	Plugin_ScrAddFunction("orderby", 	&LINQ_OrderBy);
	Plugin_ScrAddFunction("average", 	&LINQ_Average);
	Plugin_ScrAddFunction("count", 		&LINQ_Count);
	Plugin_ScrAddFunction("sum", 		&LINQ_Sum);
	Plugin_ScrAddFunction("select", 	&LINQ_Select);
	Plugin_ScrAddFunction("range", 		&LINQ_Range);
	Plugin_ScrAddFunction("repeat", 	&LINQ_Repeat);
	Plugin_ScrAddFunction("reverse", 	&LINQ_Reverse);

    // list.h
    Plugin_ScrAddFunction("listnew", 	&LIST_new);
	Plugin_ScrAddFunction("listadd", 	&LIST_add);
	Plugin_ScrAddFunction("listremove", &LIST_remove);
	Plugin_ScrAddFunction("listinsert", &LIST_insert);
	Plugin_ScrAddFunction("listlength", &LIST_length);
	Plugin_ScrAddFunction("listget", 	&LIST_get);

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
	strncpy(info->fullName, "GSC-Linq", sizeof(info->fullName));
	strncpy(info->shortDescription, "", sizeof(info->shortDescription));
	strncpy(info->longDescription, "", sizeof(info->longDescription));
}
