#include "../../dependencies/cgsc.h"
#include "../utility/utility.h"
#include <stdlib.h>
#include <string.h>

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
	uint32_t flags = GetFlagsFromGSCArray(array, length);

	if (HasFlag(flags, FLAG_STRING) || HasFlag(flags, FLAG_ISTRING))
	{
		int index = 0;
		int strLength = 0;
        qboolean hasValue = qfalse;
		for (int i = 0; i < length; i++)
		{
			if (hasValue)
			{
				if (strlen(Plugin_SL_ConvertToString(array[i]->u.stringValue)) < strLength) 
				{
					strLength = strlen(Plugin_SL_ConvertToString(array[i]->u.stringValue));
					index = i;
				}
			}
			else 
			{
				strLength = strlen(Plugin_SL_ConvertToString(array[i]->u.stringValue));
				hasValue = true;
				index = i;
			}
		}
		if (hasValue)
			Plugin_Scr_AddString(Plugin_SL_ConvertToString(array[index]->u.stringValue));
	}
	else if (HasFlag(flags, FLAG_VECTOR))
	{
		int index = 0;
		vec3_t zero;
		float distance = 0;
        qboolean hasValue = qfalse;
		for (int i = 0; i < length; i++)
		{
			if (hasValue)
			{
				if (vec_distance((float *)array[i]->u.vectorValue, zero) < distance) 
				{
					distance = vec_distance((float *)array[i]->u.vectorValue, zero);
					index = i;
				}
			}
			else 
			{
				distance = vec_distance((float *)array[i]->u.vectorValue, zero);
				hasValue = true;
				index = i;
			}
		}
		if (hasValue)
			Plugin_Scr_AddVector((float *)array[index]->u.vectorValue);
	}
	else if (HasFlag(flags, FLAG_INTEGER) || HasFlag(flags, FLAG_FLOAT))
	{
		float value = 0;
        qboolean hasValue = qfalse;
		for (int i = 0; i < length; i++)
		{
			if (array[i]->type == VAR_INTEGER)
			{
				if (hasValue)
				{
					if (array[i]->u.intValue < value) 
						value = array[i]->u.intValue;
				}
				else 
				{
					value = array[i]->u.intValue;
					hasValue = true;
				}
			}
			else if (array[i]->type == VAR_FLOAT)
			{
				if (hasValue)
				{
					if (array[i]->u.floatValue < value) 
						value = array[i]->u.floatValue;
				}
				else 
				{
					value = array[i]->u.floatValue;
					hasValue = true;
				}
			}
		}
		if (hasValue) 
		{
			if (!HasFlag(flags, FLAG_FLOAT))
				Plugin_Scr_AddInt((int)value);
			else
				Plugin_Scr_AddFloat(value);
		}
	}
	else
		Plugin_Scr_AddUndefined();

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
	uint32_t flags = GetFlagsFromGSCArray(array, length);

	if (HasFlag(flags, FLAG_STRING) || HasFlag(flags, FLAG_ISTRING))
	{
		int index = 0;
		int strLength = 0;
        qboolean hasValue = qfalse;
		for (int i = 0; i < length; i++)
		{
			if (hasValue)
			{
				if (strlen(Plugin_SL_ConvertToString(array[i]->u.stringValue)) > strLength) 
				{
					strLength = strlen(Plugin_SL_ConvertToString(array[i]->u.stringValue));
					index = i;
				}
			}
			else 
			{
				strLength = strlen(Plugin_SL_ConvertToString(array[i]->u.stringValue));
				hasValue = true;
				index = i;
			}
		}
		if (hasValue)
			Plugin_Scr_AddString(Plugin_SL_ConvertToString(array[index]->u.stringValue));
	}
	else if (HasFlag(flags, FLAG_VECTOR))
	{
		int index = 0;
		vec3_t zero;
		float distance = 0;
        qboolean hasValue = qfalse;
		for (int i = 0; i < length; i++)
		{
			if (hasValue)
			{
				if (vec_distance((float *)array[i]->u.vectorValue, zero) > distance) 
				{
					distance = vec_distance((float *)array[i]->u.vectorValue, zero);
					index = i;
				}
			}
			else 
			{
				distance = vec_distance((float *)array[i]->u.vectorValue, zero);
				hasValue = true;
				index = i;
			}
		}
		if (hasValue)
			Plugin_Scr_AddVector((float *)array[index]->u.vectorValue);
	}
	else if (HasFlag(flags, FLAG_INTEGER) || HasFlag(flags, FLAG_FLOAT))
	{
		float value = 0;
        qboolean hasValue = qfalse;
		for (int i = 0; i < length; i++)
		{
			if (array[i]->type == VAR_INTEGER)
			{
				if (hasValue)
				{
					if (array[i]->u.intValue > value) 
						value = array[i]->u.intValue;
				}
				else 
				{
					value = array[i]->u.intValue;
					hasValue = true;
				}
			}
			else if (array[i]->type == VAR_FLOAT)
			{
				if (hasValue)
				{
					if (array[i]->u.floatValue > value) 
						value = array[i]->u.floatValue;
				}
				else 
				{
					value = array[i]->u.floatValue;
					hasValue = true;
				}
			}
		}
		if (hasValue) 
		{
			if (!HasFlag(flags, FLAG_FLOAT))
				Plugin_Scr_AddInt((int)value);
			else
				Plugin_Scr_AddFloat(value);
		}
	}
	else
		Plugin_Scr_AddUndefined();

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

	Plugin_Scr_MakeArray();
	if (stricmp(typename, "string") == 0)
	{
		for (int i = 0; i < length; i++)
		{
			switch (array[i]->type)
			{
				case VAR_FLOAT:
				{
					int cpyBufferSize = snprintf(NULL, 0, "%f", array[i]->u.floatValue);
					char buffer[cpyBufferSize];
					snprintf(buffer, cpyBufferSize, "%f", array[i]->u.floatValue);
					Plugin_Scr_AddString(buffer);
					Plugin_Scr_AddArray();
					break;
				}
				case VAR_INTEGER:
				{
					int cpyBufferSize = snprintf(NULL, 0, "%d", array[i]->u.intValue);
					char buffer[cpyBufferSize];
					snprintf(buffer, cpyBufferSize, "%d", array[i]->u.intValue);
					Plugin_Scr_AddString(buffer);
					Plugin_Scr_AddArray();
					break;
				}
				case VAR_STRING:
				{
					Plugin_Scr_AddVariable(array[i]);
					Plugin_Scr_AddArray();
					break;
				}
				case VAR_VECTOR:
				{
					int cpyBufferSize = snprintf(NULL, 0, "(%f, %f, %f)", array[i]->u.vectorValue[0],
						array[i]->u.vectorValue[1], array[i]->u.vectorValue[2]);
					char buffer[cpyBufferSize];
					snprintf(buffer, cpyBufferSize, "(%f, %f, %f)", array[i]->u.vectorValue[0],
						array[i]->u.vectorValue[1], array[i]->u.vectorValue[2]);
					Plugin_Scr_AddString(buffer);
					Plugin_Scr_AddArray();
					break;
				}
			}
		}
	}
	else if (stricmp(typename, "int") == 0)
	{
		for (int i = 0; i < length; i++)
		{
			switch (array[i]->type)
			{
				case VAR_FLOAT:
				{
					Plugin_Scr_AddInt((int)array[i]->u.floatValue);
					Plugin_Scr_AddArray();
					break;
				}
				case VAR_INTEGER:
				{
					Plugin_Scr_AddVariable(array[i]);
					Plugin_Scr_AddArray();
					break;
				}
				case VAR_STRING:
				{
					const char *nptr = Plugin_SL_ConvertToString(array[i]->u.stringValue);
					char *endptr = NULL;
					long number = strtol(nptr, &endptr, 10);

					if (*endptr == '\0')
					{
						Plugin_Scr_AddInt((int)number);
						Plugin_Scr_AddArray();
					}
					break;
				}
			}
		}
	}
	else if (stricmp(typename, "float") == 0)
	{
		for (int i = 0; i < length; i++)
		{
			switch (array[i]->type)
			{
				case VAR_FLOAT:
				{
					Plugin_Scr_AddVariable(array[i]);
					Plugin_Scr_AddArray();
					break;
				}
				case VAR_INTEGER:
				{
					Plugin_Scr_AddFloat((float)array[i]->u.intValue);
					Plugin_Scr_AddArray();
					break;
				}
				case VAR_STRING:
				{
					const char *nptr = Plugin_SL_ConvertToString(array[i]->u.stringValue);
					char *endptr = NULL;
					float number = strtof(nptr, &endptr);

					if (*endptr == '\0')
					{
						Plugin_Scr_AddFloat(number);
						Plugin_Scr_AddArray();
					}
					break;
				}
			}
		}
	}
	Plugin_Scr_FreeArray(array, length);
}

void LINQ_OfType()
{
	if (Plugin_Scr_GetNumParam() != 3)
	{
		Plugin_Scr_Error("Usage: ofType(<array>, <array_size>, <type>)");
		return;
	}
	VariableValue **array = Plugin_Scr_GetArray(0);
	const uint32_t length = Plugin_Scr_GetInt(1);
	const char *typename = Plugin_Scr_GetString(2);

	Plugin_Scr_MakeArray();
	for (int i = 0; i < length; i++)
	{
		switch (array[i]->type)
		{
			case VAR_INTEGER:
				if (stricmp(typename, "int") == 0)
				{
					Plugin_Scr_AddVariable(array[i]);
					Plugin_Scr_AddArray();
				}
				break;
			case VAR_FLOAT:
				if (stricmp(typename, "float") == 0)
				{
					Plugin_Scr_AddVariable(array[i]);
					Plugin_Scr_AddArray();
				}
				break;
			case VAR_ISTRING:
			case VAR_STRING:
				if (stricmp(typename, "string") == 0)
				{
					Plugin_Scr_AddVariable(array[i]);
					Plugin_Scr_AddArray();
				}
				break;
			case VAR_VECTOR:
				if (stricmp(typename, "vector") == 0)
				{
					Plugin_Scr_AddVariable(array[i]);
					Plugin_Scr_AddArray();
				}
				break;
			case VAR_POINTER:
			{
				switch (Plugin_Scr_GetObjectType(array[i]->u.pointerValue))
				{
					case VAR_ARRAY:
						if (stricmp(typename, "array") == 0)
						{
							Plugin_Scr_AddVariable(array[i]);
							Plugin_Scr_AddArray();
						}
						break;
					case VAR_OBJECT:
						if (stricmp(typename, "struct") == 0)
						{
							Plugin_Scr_AddVariable(array[i]);
							Plugin_Scr_AddArray();
						}
						break;
				}
			}
			break;
		}
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
	uint32_t flags = GetFlagsFromGSCArray(array, length);

	if (IsFlag(flags, FLAG_FLOAT) || IsFlag(flags, FLAG_INTEGER) || IsFlag(flags, FLAG_STRING)
		|| IsFlag(flags, FLAG_ISTRING) || IsFlag(flags, FLAG_VECTOR))
	{
		Plugin_Scr_MakeArray();
		if (IsFlag(flags, FLAG_FLOAT))
			qsort(array, length, sizeof(VariableValue *), gsc_float_cmp);
		else if (IsFlag(flags, FLAG_INTEGER))
			qsort(array, length, sizeof(VariableValue *), gsc_int_cmp);
		else if (IsFlag(flags, FLAG_STRING) || IsFlag(flags, FLAG_ISTRING))
			qsort(array, length, sizeof(VariableValue *), gsc_cstring_cmp);
		else if (IsFlag(flags, FLAG_VECTOR))
			qsort(array, length, sizeof(VariableValue *), gsc_vec3_cmp);

		for (int i = 0; i < length; i++)
		{
			Plugin_Scr_AddVariable(array[i]);
			Plugin_Scr_AddArray();
		}
	}
	else
		Plugin_Scr_AddUndefined();

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
	int count = 0;
	const uint32_t flags = GetFlagsFromGSCArray(array, length);

	if (IsFlag(flags, FLAG_VECTOR))
	{
		vec3_t vec;
		for (int i = 0; i < length; i++)
		{
			if (array[i]->type == VAR_VECTOR)
			{
				vec[0] += array[i]->u.vectorValue[0];
				vec[1] += array[i]->u.vectorValue[1];
				vec[2] += array[i]->u.vectorValue[2];
				count++;
			}
		}
		vec[0] /= count;
		vec[1] /= count;
		vec[2] /= count;
		Plugin_Scr_AddVector(vec);
	}
	else
	{
		float sum = 0;
		for (int i = 0; i < length; i++)
		{
			if (array[i]->type == VAR_FLOAT)
				sum += array[i]->u.floatValue;
			else
				sum += array[i]->u.intValue;
			count++;
		}
		Plugin_Scr_AddFloat(sum / count);
	}

	Plugin_Scr_FreeArray(array, length);
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
	else if (HasFlag(flags, FLAG_VECTOR))
	{
		vec3_t sum;
		for (int i = 0; i < length; i++)
		{
			if (array[i]->type == VAR_VECTOR)
			{
				sum[0] += array[i]->u.vectorValue[0];
				sum[1] += array[i]->u.vectorValue[1];
				sum[2] += array[i]->u.vectorValue[2];
			}
		}
		Plugin_Scr_AddVector(sum);
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

	//Plugin_Scr_MakeArray();
	for (int i = 0; i < length; i++)
	{
		// Call delegate(item)
		Plugin_Scr_AddVariable(array[i]);
		__attribute__((unused)) const short tid = Plugin_Scr_ExecThread(threadId, 1);

		// GSC return variable - try #1
		//const register int varType asm("esi");
		//const register int varAddr asm("ebx");
		//VariableValue *var = (VariableValue *)malloc(sizeof(VariableValue));
		//var->u = *(union VariableUnion *)varAddr;
		//var->type = varType;

		// GSC return variable - try #2
		//const register int varAddr asm("ecx");
		//const register int varUnion asm("edx");
		//VariableValue *var = (VariableValue *)malloc(sizeof(VariableValue));
		//var->type = ((VariableThreadReturn *)varAddr)->type;
		//var->u = (union VariableUnion)varUnion;
		
		//Plugin_Scr_AddVariable(var);
		//Plugin_Scr_AddArray();
		//Plugin_Scr_FreeThread(tid);
		//free(var);
	}
	Plugin_Scr_FreeArray(array, length);
	Plugin_Printf("LINQ_Select is not implemented yet.\n");
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
