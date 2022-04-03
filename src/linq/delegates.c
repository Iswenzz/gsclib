#include "delegates.h"

#include <cgsc.h>
#include <stdlib.h>

void GScr_LINQ_Select()
{
	if (CGSC_Unsupported(CGSC_EQ(3)))
	{
		Plugin_Scr_AddUndefined();
		return;
	}
	if (Plugin_Scr_GetNumParam() != 2)
	{
		Plugin_Scr_Error("Usage: Select(<array>, <::delegate>)");
		return;
	}

	VariableValueArray *array = Plugin_Scr_GetArray(0);
	const int threadId = Plugin_Scr_GetFunc(1);

	Plugin_Scr_MakeArray();
	for (int i = 0; i < array->length; i++)
	{
		// Call delegate(item)
		Plugin_Scr_AddVariable(array->items[i]);
		const short tid = Plugin_Scr_ExecThreadResult(threadId, 1);
		VariableValue* var = Plugin_Scr_AllocReturnResult();
		
		Plugin_Scr_AddVariable(var);
		Plugin_Scr_AddArray();
		Plugin_Scr_FreeThread(tid);
	}
	Plugin_Scr_FreeArray(array);
}
