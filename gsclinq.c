#include "cgsc.h"
#include "gsclinq.h"

void LINQ_All()
{
	if (Plugin_Scr_GetNumParam() != 3)
    {
		Plugin_Scr_Error("Usage: all(<array>, <array size>, <::function>)");
		return;
    }
	VariableValue **array = Plugin_Scr_GetArray(0);
	const uint32_t length = Plugin_Scr_GetInt(1);
	const uint32_t threadId = Plugin_Scr_GetFunc(2);
	qboolean result = qtrue;

	for (int i = 0; i < length; i++)
	{
		// Call predicate(item)
		Plugin_Scr_AddVariable(array[i]);
		const short tid = Plugin_Scr_ExecThread(threadId, 1);
		const register int *gscPredicate asm("edx");

		if (!*gscPredicate)
		{
			result = qfalse;
			Plugin_Scr_FreeThread(tid);
			break;
		}
		Plugin_Scr_FreeThread(tid);
	}
	Plugin_Scr_FreeArray(array, length);
	Plugin_Scr_AddBool(result);
}

void LINQ_Where()
{
	if (Plugin_Scr_GetNumParam() != 3)
	{
		Plugin_Scr_Error("Usage: where(<array>, <array_size>, <::function>)");
		return;
	}
	VariableValue **array = Plugin_Scr_GetArray(0);
	const uint32_t length = Plugin_Scr_GetInt(1);
	const uint32_t threadId = Plugin_Scr_GetFunc(2);

	Plugin_Scr_MakeArray();
	for (int i = 0; i < length; i++)
	{
		// Call predicate(item)
		Plugin_Scr_AddVariable(array[i]);
		const short tid = Plugin_Scr_ExecThread(threadId, 1);
		const register int *gscPredicate asm("edx");

		if (*gscPredicate)
		{
			Plugin_Scr_AddVariable(array[i]);
			Plugin_Scr_AddArray();
		}
		Plugin_Scr_FreeThread(tid);
	}
	Plugin_Scr_FreeArray(array, length);
}

void comPrintf()
{
	if (Plugin_Scr_GetNumParam() != 1)
    {
        Plugin_Scr_Error("Usage: comPrintf(<string>)");
        return;
    }
	Plugin_Printf(Plugin_Scr_GetString(0));
}

PCL int OnInit()
{
	Plugin_ScrAddFunction("comPrintf", 		&comPrintf);
	Plugin_ScrAddFunction("all", 			&LINQ_All);
	Plugin_ScrAddFunction("where", 			&LINQ_Where);

	return 0;
}

PCL void OnInfoRequest(pluginInfo_t *info)
{ 
	// Function used to obtain information about the plugin
	// Memory pointed by info is allocated by the server binary

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
