#include "delegates.h"

#include <cgsc.h>
#include <stdlib.h>

void GScr_LINQ_Select()
{
	if (Plugin_Scr_GetNumParam() != 2)
	{
		Plugin_Scr_Error("Usage: Select(<array>, <::delegate>)");
		return;
	}

	#if CGSC(4)
	VariableValueArray *array = Plugin_Scr_GetArray(0);
	const uint32_t threadId = Plugin_Scr_GetFunc(1);

	Plugin_Scr_MakeArray();
	for (int i = 0; i < array->length; i++)
	{
		// Call delegate(item)
		Plugin_Scr_AddVariable(array->items[i]);
		const short tid = Plugin_Scr_ExecThreadResult(threadId, 1);
		VariableValue *var = Plugin_Scr_AllocReturnResult();
		
		Plugin_Scr_AddVariable(var);
		Plugin_Scr_AddArray();
		Plugin_Scr_FreeThread(tid);
		free(var);
	}
	Plugin_Scr_FreeArray(array);
	#endif

	#if CGSC_EQ(3)
	Plugin_PrintError("LINQ_Select is unsupported for this version.");
	Plugin_Scr_AddUndefined();
	#endif
}
