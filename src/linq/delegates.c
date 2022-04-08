#include "delegates.h"

#include <cgsc.h>
#include <stdlib.h>

void GScr_LINQ_Select()
{
	CHECK_PARAMS(2, "Usage: Select(<array>, <::delegate>)");
	CHECK_UNSUPPORTED(CGSC_EQ(3));

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

void GScr_LINQ_Foreach()
{
	CHECK_PARAMS(2, "Usage: Foreach(<array>, <::delegate>)");
	CHECK_UNSUPPORTED(CGSC_EQ(3));

	VariableValueArray* array = Plugin_Scr_GetArray(0);
	const int threadId = Plugin_Scr_GetFunc(1);

	for (int i = 0; i < array->length; i++)
	{
		// Call delegate(item)
		Plugin_Scr_AddVariable(array->items[i]);
		const short tid = Plugin_Scr_ExecThreadResult(threadId, 1);

		Plugin_Scr_FreeThread(tid);
	}
	Plugin_Scr_FreeArray(array);
}
