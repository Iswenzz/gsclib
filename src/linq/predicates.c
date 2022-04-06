#include "predicates.h"
#include <cgsc.h>

void GScr_LINQ_All()
{
	if (Plugin_Scr_GetNumParam() != 2)
	{
		Plugin_Scr_Error("Usage: All(<array>, <::predicate>)");
		return;
	}
	VariableValueArray *array = Plugin_Scr_GetArray(0);
	const int threadId = Plugin_Scr_GetFunc(1);
	qboolean result = qtrue;

	for (int i = 0; i < array->length; i++)
	{
		// Call predicate(item)
		Plugin_Scr_AddVariable(array->items[i]);
		const short tid = Plugin_Scr_ExecThread(threadId, 1);

		if (!Plugin_Scr_GetThreadReturn())
		{
			result = qfalse;
			Plugin_Scr_FreeThread(tid);
			break;
		}
		Plugin_Scr_FreeThread(tid);
	}
	Plugin_Scr_FreeArray(array);
	Plugin_Scr_AddBool(result);
}

void GScr_LINQ_Any()
{
	if (Plugin_Scr_GetNumParam() != 2)
	{
		Plugin_Scr_Error("Usage: Any(<array>, <::predicate>)");
		return;
	}
	VariableValueArray *array = Plugin_Scr_GetArray(0);
	const int threadId = Plugin_Scr_GetFunc(1);
	qboolean result = qfalse;

	for (int i = 0; i < array->length; i++)
	{
		// Call predicate(item)
		Plugin_Scr_AddVariable(array->items[i]);
		const short tid = Plugin_Scr_ExecThread(threadId, 1);

		if (Plugin_Scr_GetThreadReturn())
		{
			result = qtrue;
			Plugin_Scr_FreeThread(tid);
			break;
		}
		Plugin_Scr_FreeThread(tid);
	}
	Plugin_Scr_FreeArray(array);
	Plugin_Scr_AddBool(result);
}

void GScr_LINQ_Where()
{
	if (Plugin_Scr_GetNumParam() != 2)
	{
		Plugin_Scr_Error("Usage: Where(<array>, <::predicate>)");
		return;
	}
	VariableValueArray *array = Plugin_Scr_GetArray(0);
	const int threadId = Plugin_Scr_GetFunc(1);

	Plugin_Scr_MakeArray();
	for (int i = 0; i < array->length; i++)
	{
		// Call predicate(item)
		Plugin_Scr_AddVariable(array->items[i]);
		const short tid = Plugin_Scr_ExecThread(threadId, 1);

		if (Plugin_Scr_GetThreadReturn())
		{
			Plugin_Scr_AddVariable(array->items[i]);
			Plugin_Scr_AddArray();
		}
		Plugin_Scr_FreeThread(tid);
	}
	Plugin_Scr_FreeArray(array);
}

void GScr_LINQ_Last()
{
	if (Plugin_Scr_GetNumParam() != 2)
	{
		Plugin_Scr_Error("Usage: Last(<array>, <::predicate>)");
		return;
	}
	VariableValueArray *array = Plugin_Scr_GetArray(0);
	const int threadId = Plugin_Scr_GetFunc(1);
	VariableValue *last = NULL;

	for (int i = 0; i < array->length; i++)
	{
		// Call predicate(item)
		Plugin_Scr_AddVariable(array->items[i]);
		const short tid = Plugin_Scr_ExecThread(threadId, 1);

		if (Plugin_Scr_GetThreadReturn())
			last = array->items[i];
		Plugin_Scr_FreeThread(tid);
	}
	if (last != NULL)
		Plugin_Scr_AddVariable(last);
	else
		Plugin_Scr_AddUndefined();
	Plugin_Scr_FreeArray(array);
}

void GScr_LINQ_First()
{
	if (Plugin_Scr_GetNumParam() != 2)
	{
		Plugin_Scr_Error("Usage: First(<array>, <::predicate>)");
		return;
	}
	VariableValueArray *array = Plugin_Scr_GetArray(0);
	const int threadId = Plugin_Scr_GetFunc(1);

	for (int i = 0; i < array->length; i++)
	{
		// Call predicate(item)
		Plugin_Scr_AddVariable(array->items[i]);
		const short tid = Plugin_Scr_ExecThread(threadId, 1);

		if (Plugin_Scr_GetThreadReturn())
		{
			Plugin_Scr_AddVariable(array->items[i]);
			Plugin_Scr_FreeThread(tid);
			break;
		}
		Plugin_Scr_FreeThread(tid);
	}
	Plugin_Scr_FreeArray(array);
}

void GScr_LINQ_Count()
{
	if (Plugin_Scr_GetNumParam() != 2)
	{
		Plugin_Scr_Error("Usage: Count(<array>, <::predicate>)");
		return;
	}
	VariableValueArray *array = Plugin_Scr_GetArray(0);
	const int threadId = Plugin_Scr_GetFunc(1);
	int result = 0;

	for (int i = 0; i < array->length; i++)
	{
		// Call predicate(item)
		Plugin_Scr_AddVariable(array->items[i]);
		const short tid = Plugin_Scr_ExecThread(threadId, 1);

		if (Plugin_Scr_GetThreadReturn())
			result++;

		Plugin_Scr_FreeThread(tid);
	}
	Plugin_Scr_FreeArray(array);
	Plugin_Scr_AddInt(result);
}
