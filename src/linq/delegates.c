#include "delegates.h"

#include <CGSC/cgsc.h>
#include <stdlib.h>

void GScr_LINQ_Select()
{
	CHECK_PARAMS(2, "Usage: Select(<array>, <::delegate>)");
	CHECK_UNSUPPORTED(CGSC_EQ(3));

	VariableValueArray array = Plugin_Scr_GetArray(0);
	const int threadId = Plugin_Scr_GetFunction(1);

	Plugin_Scr_MakeArray();
	for (int i = 0; i < array.length; i++)
	{
		// Call delegate(item)
		Plugin_Scr_AddInt(i);
		Plugin_Scr_AddVariable(array.items[i]);
		const short tid = Plugin_Scr_ExecThreadResult(threadId, 2);
		VariableValue var = Plugin_Scr_ReturnResult();

		Plugin_Scr_AddVariable(var);
		Plugin_Scr_AddArray();
		Plugin_Scr_FreeThread(tid);
	}
	Plugin_Scr_FreeArray(&array);
}

void GScr_LINQ_Foreach()
{
	CHECK_PARAMS(2, "Usage: Foreach(<array>, <::delegate>)");
	CHECK_UNSUPPORTED(CGSC_EQ(3));

	VariableValueArray array = Plugin_Scr_GetArray(0);
	const int threadId = Plugin_Scr_GetFunction(1);

	for (int i = 0; i < array.length; i++)
	{
		// Call delegate(item)
		Plugin_Scr_AddInt(i);
		Plugin_Scr_AddVariable(array.items[i]);
		const short tid = Plugin_Scr_ExecThreadResult(threadId, 2);

		Plugin_Scr_FreeThread(tid);
	}
	Plugin_Scr_FreeArray(&array);
}

void GScr_LINQ_Aggregate()
{
	CHECK_PARAMS(3, "Usage: Aggregate(<initialValue>, <array>, <::delegate>)");
	CHECK_UNSUPPORTED(CGSC_EQ(3));

	VariableValue previousValue = *Plugin_Scr_SelectParam(0);
	VariableValueArray array = Plugin_Scr_GetArray(1);
	const int threadId = Plugin_Scr_GetFunction(2);

	for (int i = 0; i < array.length; i++)
	{
		// Call delegate(item)
		Plugin_Scr_AddInt(i);
		Plugin_Scr_AddVariable(array.items[i]);
		Plugin_Scr_AddVariable(previousValue);
		const short tid = Plugin_Scr_ExecThreadResult(threadId, 3);
		previousValue = Plugin_Scr_ReturnResult();

		Plugin_Scr_FreeThread(tid);
	}
	Plugin_Scr_FreeArray(&array);
	Plugin_Scr_AddVariable(previousValue);
}
