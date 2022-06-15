#include "predicates.h"
#include <cgsc.h>

void GScr_LINQ_All()
{
	CHECK_PARAMS(2, "Usage: All(<array>, <::predicate>)");

	VariableValueArray array = Plugin_Scr_GetArray(0);
	const int threadId = Plugin_Scr_GetFunction(1);
	qboolean result = qtrue;

	for (int i = 0; i < array.length; i++)
	{
		// Call predicate(item)
		Plugin_Scr_AddInt(i);
		Plugin_Scr_AddVariable(array.items[i]);
		const short tid = Plugin_Scr_ExecThread(threadId, 2);

		if (!Plugin_Scr_GetThreadReturn())
		{
			result = qfalse;
			Plugin_Scr_FreeThread(tid);
			break;
		}
		Plugin_Scr_FreeThread(tid);
	}
	Plugin_Scr_FreeArray(&array);
	Plugin_Scr_AddBool(result);
}

void GScr_LINQ_Any()
{
	CHECK_PARAMS(2, "Usage: Any(<array>, <::predicate>)");

	VariableValueArray array = Plugin_Scr_GetArray(0);
	const int threadId = Plugin_Scr_GetFunction(1);
	qboolean result = qfalse;

	for (int i = 0; i < array.length; i++)
	{
		// Call predicate(item)
		Plugin_Scr_AddInt(i);
		Plugin_Scr_AddVariable(array.items[i]);
		const short tid = Plugin_Scr_ExecThread(threadId, 2);

		if (Plugin_Scr_GetThreadReturn())
		{
			result = qtrue;
			Plugin_Scr_FreeThread(tid);
			break;
		}
		Plugin_Scr_FreeThread(tid);
	}
	Plugin_Scr_FreeArray(&array);
	Plugin_Scr_AddBool(result);
}

void GScr_LINQ_Where()
{
	CHECK_PARAMS(2, "Usage: Where(<array>, <::predicate>)");

	VariableValueArray array = Plugin_Scr_GetArray(0);
	const int threadId = Plugin_Scr_GetFunction(1);

	Plugin_Scr_MakeArray();
	for (int i = 0; i < array.length; i++)
	{
		// Call predicate(item)
		Plugin_Scr_AddInt(i);
		Plugin_Scr_AddVariable(array.items[i]);
		const short tid = Plugin_Scr_ExecThread(threadId, 2);

		if (Plugin_Scr_GetThreadReturn())
		{
			Plugin_Scr_AddVariable(array.items[i]);
			Plugin_Scr_AddArray();
		}
		Plugin_Scr_FreeThread(tid);
	}
	Plugin_Scr_FreeArray(&array);
}

void GScr_LINQ_Last()
{
	CHECK_PARAMS(2, "Usage: Last(<array>, <::predicate>)");

	VariableValueArray array = Plugin_Scr_GetArray(0);
	const int threadId = Plugin_Scr_GetFunction(1);
	VariableValue *last = NULL;

	for (int i = 0; i < array.length; i++)
	{
		// Call predicate(item)
		Plugin_Scr_AddInt(i);
		Plugin_Scr_AddVariable(array.items[i]);
		const short tid = Plugin_Scr_ExecThread(threadId, 2);

		if (Plugin_Scr_GetThreadReturn())
			last = &array.items[i];
		Plugin_Scr_FreeThread(tid);
	}
	if (last != NULL)
		Plugin_Scr_AddVariable(*last);
	Plugin_Scr_FreeArray(&array);
}

void GScr_LINQ_First()
{
	CHECK_PARAMS(2, "Usage: First(<array>, <::predicate>)");

	VariableValueArray array = Plugin_Scr_GetArray(0);
	const int threadId = Plugin_Scr_GetFunction(1);

	for (int i = 0; i < array.length; i++)
	{
		// Call predicate(item)
		Plugin_Scr_AddInt(i);
		Plugin_Scr_AddVariable(array.items[i]);
		const short tid = Plugin_Scr_ExecThread(threadId, 2);

		if (Plugin_Scr_GetThreadReturn())
		{
			Plugin_Scr_AddVariable(array.items[i]);
			Plugin_Scr_FreeThread(tid);
			break;
		}
		Plugin_Scr_FreeThread(tid);
	}
	Plugin_Scr_FreeArray(&array);
}

void GScr_LINQ_Count()
{
	CHECK_PARAMS(2, "Usage: Count(<array>, <::predicate>)");

	VariableValueArray array = Plugin_Scr_GetArray(0);
	const int threadId = Plugin_Scr_GetFunction(1);
	int result = 0;

	for (int i = 0; i < array.length; i++)
	{
		// Call predicate(item)
		Plugin_Scr_AddInt(i);
		Plugin_Scr_AddVariable(array.items[i]);
		const short tid = Plugin_Scr_ExecThread(threadId, 2);

		if (Plugin_Scr_GetThreadReturn())
			result++;

		Plugin_Scr_FreeThread(tid);
	}
	Plugin_Scr_FreeArray(&array);
	Plugin_Scr_AddInt(result);
}
