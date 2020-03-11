#include "../../dependencies/cgsc.h"
#include <stdlib.h>

void LINQ_All()
{
	if (Plugin_Scr_GetNumParam() != 3)
    {
		Plugin_Scr_Error("Usage: all(<array>, <array size>, <::predicate>)");
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

void LINQ_Reverse()
{
	if (Plugin_Scr_GetNumParam() != 2)
    {
		Plugin_Scr_Error("Usage: reverse(<array>, <array size>)");
		return;
    }
	VariableValue **array = Plugin_Scr_GetArray(0);
	const uint32_t length = Plugin_Scr_GetInt(1);

	Plugin_Scr_MakeArray();
	for (int i = length - 1; i > -1; i--)
	{
		Plugin_Scr_AddVariable(array[i]);
		Plugin_Scr_AddArray();
	}
	Plugin_Scr_FreeArray(array, length);
}

void LINQ_Any()
{
	if (Plugin_Scr_GetNumParam() != 3)
    {
		Plugin_Scr_Error("Usage: any(<array>, <array size>, <::predicate>)");
		return;
    }
	VariableValue **array = Plugin_Scr_GetArray(0);
	const uint32_t length = Plugin_Scr_GetInt(1);
	const uint32_t threadId = Plugin_Scr_GetFunc(2);
	qboolean result = qfalse;

	for (int i = 0; i < length; i++)
	{
		// Call predicate(item)
		Plugin_Scr_AddVariable(array[i]);
		const short tid = Plugin_Scr_ExecThread(threadId, 1);
		const register int *gscPredicate asm("edx");

		if (*gscPredicate)
		{
			result = qtrue;
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
		Plugin_Scr_Error("Usage: where(<array>, <array_size>, <::predicate>)");
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

void LINQ_Min()
{
	if (Plugin_Scr_GetNumParam() != 2)
	{
		Plugin_Scr_Error("Usage: min(<array>, <array_size>)");
		return;
	}
	VariableValue **array = Plugin_Scr_GetArray(0);
	const uint32_t length = Plugin_Scr_GetInt(1);

	for (int i = 0; i < length; i++)
	{
		// TODO type sort in their own function
	}
	Plugin_Scr_FreeArray(array, length);
}

void LINQ_Max()
{
	if (Plugin_Scr_GetNumParam() != 2)
	{
		Plugin_Scr_Error("Usage: max(<array>, <array_size>)");
		return;
	}
	VariableValue **array = Plugin_Scr_GetArray(0);
	const uint32_t length = Plugin_Scr_GetInt(1);

	for (int i = 0; i < length; i++)
	{
		// TODO type sort in their own function
	}
	Plugin_Scr_FreeArray(array, length);
}

void LINQ_Last()
{
	if (Plugin_Scr_GetNumParam() != 3)
    {
		Plugin_Scr_Error("Usage: last(<array>, <array size>, <::predicate>)");
		return;
    }
	VariableValue **array = Plugin_Scr_GetArray(0);
	const uint32_t length = Plugin_Scr_GetInt(1);
	const uint32_t threadId = Plugin_Scr_GetFunc(2);
	VariableValue *last = NULL;

	for (int i = 0; i < length; i++)
	{
		// Call predicate(item)
		Plugin_Scr_AddVariable(array[i]);
		const short tid = Plugin_Scr_ExecThread(threadId, 1);
		const register int *gscPredicate asm("edx");

		if (*gscPredicate)
			last = array[i];
		Plugin_Scr_FreeThread(tid);
	}
	Plugin_Scr_AddVariable(last);
	Plugin_Scr_FreeArray(array, length);
}

void LINQ_First()
{
	if (Plugin_Scr_GetNumParam() != 3)
    {
		Plugin_Scr_Error("Usage: first(<array>, <array size>, <::predicate>)");
		return;
    }
	VariableValue **array = Plugin_Scr_GetArray(0);
	const uint32_t length = Plugin_Scr_GetInt(1);
	const uint32_t threadId = Plugin_Scr_GetFunc(2);

	for (int i = 0; i < length; i++)
	{
		// Call predicate(item)
		Plugin_Scr_AddVariable(array[i]);
		const short tid = Plugin_Scr_ExecThread(threadId, 1);
		const register int *gscPredicate asm("edx");

		if (*gscPredicate)
		{
			Plugin_Scr_AddVariable(array[i]);
			Plugin_Scr_FreeThread(tid);
			break;
		}
		Plugin_Scr_FreeThread(tid);
	}
	Plugin_Scr_FreeArray(array, length);
}

void LINQ_Cast()
{
	if (Plugin_Scr_GetNumParam() != 3)
	{
		Plugin_Scr_Error("Usage: cast(<array>, <array_size>, <type>)");
		return;
	}
	VariableValue **array = Plugin_Scr_GetArray(0);
	const uint32_t length = Plugin_Scr_GetInt(1);
	const char *typename = Plugin_Scr_GetString(2);

	for (int i = 0; i < length; i++)
	{
		// TODO type sort in their own function
	}
	Plugin_Scr_FreeArray(array, length);
}

void LINQ_Sort()
{
	if (Plugin_Scr_GetNumParam() != 2)
	{
		Plugin_Scr_Error("Usage: sort(<array>, <array_size>)");
		return;
	}
	VariableValue **array = Plugin_Scr_GetArray(0);
	const uint32_t length = Plugin_Scr_GetInt(1);

	for (int i = 0; i < length; i++)
	{
		// TODO type sort in their own function
	}
	Plugin_Scr_FreeArray(array, length);
}

void LINQ_OrderBy()
{
	if (Plugin_Scr_GetNumParam() != 3)
	{
		Plugin_Scr_Error("Usage: orderby(<array>, <array_size>, <::predicate>)");
		return;
	}
	VariableValue **array = Plugin_Scr_GetArray(0);
	const uint32_t length = Plugin_Scr_GetInt(1);
	const uint32_t threadId = Plugin_Scr_GetFunc(2);

	Plugin_Scr_MakeArray();
	for (int i = 0; i < length; i++)
	{
		// TODO type sort in their own function
	}
	Plugin_Scr_FreeArray(array, length);
}

void LINQ_Average()
{
	if (Plugin_Scr_GetNumParam() != 2)
    {
		Plugin_Scr_Error("Usage: average(<array>, <array size>)");
		return;
    }
	VariableValue **array = Plugin_Scr_GetArray(0);
	const uint32_t length = Plugin_Scr_GetInt(1);
	float sum = 0, count = 0;

	for (int i = 0; i < length; i++)
	{
		if (array[i]->type == VAR_FLOAT)
			sum += array[i]->u.floatValue;
		else
			sum += array[i]->u.intValue;
		count++;
	}

	Plugin_Scr_FreeArray(array, length);
	if (length < 1 || !count)
		Plugin_Scr_AddBool(qfalse);
	else
		Plugin_Scr_AddFloat(sum / count);
}

void LINQ_Count()
{
	if (Plugin_Scr_GetNumParam() != 3)
    {
		Plugin_Scr_Error("Usage: count(<array>, <array size>, <::predicate>)");
		return;
    }
	VariableValue **array = Plugin_Scr_GetArray(0);
	const uint32_t length = Plugin_Scr_GetInt(1);
	const uint32_t threadId = Plugin_Scr_GetFunc(2);
	int result = 0;

	for (int i = 0; i < length; i++)
	{
		// Call predicate(item)
		Plugin_Scr_AddVariable(array[i]);
		const short tid = Plugin_Scr_ExecThread(threadId, 1);
		const register int *gscPredicate asm("edx");

		if (*gscPredicate)
			result++;

		Plugin_Scr_FreeThread(tid);
	}
	Plugin_Scr_FreeArray(array, length);
	Plugin_Scr_AddInt(result);
}

void LINQ_Sum()
{
	if (Plugin_Scr_GetNumParam() != 2)
	{
		Plugin_Scr_Error("Usage: sum(<array>, <array_size>)");
		return;
	}
	VariableValue **array = Plugin_Scr_GetArray(0);
	const uint32_t length = Plugin_Scr_GetInt(1);
	uint32_t flags = GetFlagsFromGSCArray(array, length);

	if (HasFlag(flags, FLAG_STRING) || HasFlag(flags, FLAG_ISTRING))
	{
		uint32_t bufferSize = 1;
		char *buffer = (char *)malloc(sizeof(char));
		char *p = buffer;
		for (int i = 0; i < length; i++)
		{
			switch (array[i]->type)
			{
				case VAR_INTEGER:
					bufferSize += snprintf(NULL, 0, "%d", array[i]->u.intValue); 
					realloc(buffer, bufferSize * sizeof(char));
					p += snprintf(p, bufferSize, "%d", array[i]->u.intValue);
					break;
				case VAR_FLOAT:
					bufferSize += snprintf(NULL, 0, "%f", array[i]->u.floatValue); 
					realloc(buffer, bufferSize * sizeof(char));
					p += snprintf(p, bufferSize, "%f", array[i]->u.floatValue);
					break;
				case VAR_STRING:
				case VAR_ISTRING:
				{
					const char *gsc_str = Plugin_SL_ConvertToString(array[i]->u.stringValue);
					bufferSize += snprintf(NULL, 0, "%s", gsc_str); 
					realloc(buffer, bufferSize * sizeof(char));
					p += snprintf(p, bufferSize, "%s", gsc_str);
					break;
				}
			}
		}
		Plugin_Scr_AddString(buffer);
		free(buffer);
	}
	else if (HasFlag(flags, FLAG_INTEGER) || HasFlag(flags, FLAG_FLOAT))
	{
		float sum = 0;
		for (int i = 0; i < length; i++)
		{
			switch (array[i]->type)
			{
				case VAR_INTEGER: sum += array[i]->u.intValue; break;
				case VAR_FLOAT: sum += array[i]->u.floatValue; break;
			}
		}
		if (!HasFlag(flags, FLAG_FLOAT))
			Plugin_Scr_AddInt((int)sum);
		else
			Plugin_Scr_AddFloat(sum);
	}
	else
		Plugin_Scr_AddUndefined();

	Plugin_Scr_FreeArray(array, length);
}

void LINQ_Select()
{
	if (Plugin_Scr_GetNumParam() != 3)
	{
		Plugin_Scr_Error("Usage: select(<array>, <array_size>, <::delegate>)");
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
		const register int *selectResult asm("edx");

		//Plugin_Scr_AddVariable(*selectResult); // TODO get returned variableValue from execthread
		Plugin_Scr_AddArray();
		Plugin_Scr_FreeThread(tid);
	}
	Plugin_Scr_FreeArray(array, length);
}

void LINQ_Range()
{
	if (Plugin_Scr_GetNumParam() != 4)
    {
		Plugin_Scr_Error("Usage: range(<array>, <array size>, <min>, <max>)");
		return;
    }
	VariableValue **array = Plugin_Scr_GetArray(0);
	const uint32_t length = Plugin_Scr_GetInt(1);
	const uint32_t min = Plugin_Scr_GetInt(2);
	const uint32_t max = Plugin_Scr_GetInt(3);

	if (min >= max || max < min)
	{
		Plugin_Scr_Error("range() - wrong min/max value");
		return;
    }

	Plugin_Scr_MakeArray();
	for (int i = min; i < max; i++)
	{
		Plugin_Scr_AddVariable(array[i]);
		Plugin_Scr_AddArray();
	}
	Plugin_Scr_FreeArray(array, length);
}

void LINQ_Repeat()
{
	if (Plugin_Scr_GetNumParam() != 3)
    {
		Plugin_Scr_Error("Usage: repeat(<array>, <array size>, <count>)");
		return;
    }
	VariableValue **array = Plugin_Scr_GetArray(0);
	const uint32_t length = Plugin_Scr_GetInt(1);
	const uint32_t count = Plugin_Scr_GetInt(2);

	Plugin_Scr_MakeArray();
	for (int r = 0; r < count; r++)
	{
		for (int i = 0; i < length; i++)
		{
			Plugin_Scr_AddVariable(array[i]);
			Plugin_Scr_AddArray();
		}
	}
	Plugin_Scr_FreeArray(array, length);
}