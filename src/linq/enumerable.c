#include "enumerable.h"
#include "../utility/polycmp.h"
#include "../utility/util.h"
#include <cgsc.h>
#include <stdlib.h>
#include <string.h>

void GScr_LINQ_Reverse()
{
	if (Plugin_Scr_GetNumParam() != 1)
	{
		Plugin_Scr_Error("Usage: Reverse(<array>)");
		return;
	}
	VariableValueArray *array = Plugin_Scr_GetArray(0);

	Plugin_Scr_MakeArray();
	for (int i = array->length - 1; i > -1; i--)
	{
		Plugin_Scr_AddVariable(array->items[i]);
		Plugin_Scr_AddArray();
	}
	Plugin_Scr_FreeArray(array);
}

void GScr_LINQ_Min()
{
	if (Plugin_Scr_GetNumParam() != 1)
	{
		Plugin_Scr_Error("Usage: Min(<array>)");
		return;
	}
	VariableValueArray *array = Plugin_Scr_GetArray(0);
	uint32_t flags = Plugin_GetFlagsFromGSCArray(array);

	if (HasFlag(flags, FLAG_STRING) || HasFlag(flags, FLAG_ISTRING))
	{
		int index = 0;
		int strLength = 0;
		qboolean hasValue = qfalse;
		for (int i = 0; i < array->length; i++)
		{
			if (hasValue)
			{
				if (strlen(Plugin_SL_ConvertToString(array->items[i]->u.stringValue)) < strLength) 
				{
					strLength = strlen(Plugin_SL_ConvertToString(array->items[i]->u.stringValue));
					index = i;
				}
			}
			else 
			{
				strLength = strlen(Plugin_SL_ConvertToString(array->items[i]->u.stringValue));
				hasValue = qtrue;
				index = i;
			}
		}
		if (hasValue)
			Plugin_Scr_AddString(Plugin_SL_ConvertToString(array->items[index]->u.stringValue));
		else
			Plugin_Scr_AddUndefined();
	}
	else if (HasFlag(flags, FLAG_VECTOR))
	{
		int index = 0;
		vec3_t zero = { 0, 0, 0 };
		float distance = 0;
		qboolean hasValue = qfalse;
		for (int i = 0; i < array->length; i++)
		{
			if (hasValue)
			{
				if (vec_distance((float *)array->items[i]->u.vectorValue, zero) < distance) 
				{
					distance = vec_distance((float *)array->items[i]->u.vectorValue, zero);
					index = i;
				}
			}
			else 
			{
				distance = vec_distance((float *)array->items[i]->u.vectorValue, zero);
				hasValue = qtrue;
				index = i;
			}
		}
		if (hasValue)
			Plugin_Scr_AddVector((float *)array->items[index]->u.vectorValue);
		else
			Plugin_Scr_AddUndefined();
	}
	else if (HasFlag(flags, FLAG_INTEGER) || HasFlag(flags, FLAG_FLOAT))
	{
		float value = 0;
		qboolean hasValue = qfalse;
		for (int i = 0; i < array->length; i++)
		{
			if (array->items[i]->type == VAR_INTEGER)
			{
				if (hasValue)
				{
					if (array->items[i]->u.intValue < value) 
						value = array->items[i]->u.intValue;
				}
				else 
				{
					value = array->items[i]->u.intValue;
					hasValue = qtrue;
				}
			}
			else if (array->items[i]->type == VAR_FLOAT)
			{
				if (hasValue)
				{
					if (array->items[i]->u.floatValue < value) 
						value = array->items[i]->u.floatValue;
				}
				else 
				{
					value = array->items[i]->u.floatValue;
					hasValue = qtrue;
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
		else
			Plugin_Scr_AddUndefined();
	}
	else
		Plugin_Scr_AddUndefined();

	Plugin_Scr_FreeArray(array);
}

void GScr_LINQ_Max()
{
	if (Plugin_Scr_GetNumParam() != 1)
	{
		Plugin_Scr_Error("Usage: Max(<array>)");
		return;
	}
	VariableValueArray *array = Plugin_Scr_GetArray(0);
	uint32_t flags = Plugin_GetFlagsFromGSCArray(array);

	if (HasFlag(flags, FLAG_STRING) || HasFlag(flags, FLAG_ISTRING))
	{
		int index = 0;
		int strLength = 0;
		qboolean hasValue = qfalse;
		for (int i = 0; i < array->length; i++)
		{
			if (hasValue)
			{
				if (strlen(Plugin_SL_ConvertToString(array->items[i]->u.stringValue)) > strLength) 
				{
					strLength = strlen(Plugin_SL_ConvertToString(array->items[i]->u.stringValue));
					index = i;
				}
			}
			else 
			{
				strLength = strlen(Plugin_SL_ConvertToString(array->items[i]->u.stringValue));
				hasValue = qtrue;
				index = i;
			}
		}
		if (hasValue)
			Plugin_Scr_AddString(Plugin_SL_ConvertToString(array->items[index]->u.stringValue));
	}
	else if (HasFlag(flags, FLAG_VECTOR))
	{
		int index = 0;
		vec3_t zero = { 0, 0, 0 };
		float distance = 0;
		qboolean hasValue = qfalse;
		for (int i = 0; i < array->length; i++)
		{
			if (hasValue)
			{
				if (vec_distance((float *)array->items[i]->u.vectorValue, zero) > distance) 
				{
					distance = vec_distance((float *)array->items[i]->u.vectorValue, zero);
					index = i;
				}
			}
			else 
			{
				distance = vec_distance((float *)array->items[i]->u.vectorValue, zero);
				hasValue = qtrue;
				index = i;
			}
		}
		if (hasValue)
			Plugin_Scr_AddVector((float *)array->items[index]->u.vectorValue);
	}
	else if (HasFlag(flags, FLAG_INTEGER) || HasFlag(flags, FLAG_FLOAT))
	{
		float value = 0;
		qboolean hasValue = qfalse;
		for (int i = 0; i < array->length; i++)
		{
			if (array->items[i]->type == VAR_INTEGER)
			{
				if (hasValue)
				{
					if (array->items[i]->u.intValue > value) 
						value = array->items[i]->u.intValue;
				}
				else 
				{
					value = array->items[i]->u.intValue;
					hasValue = qtrue;
				}
			}
			else if (array->items[i]->type == VAR_FLOAT)
			{
				if (hasValue)
				{
					if (array->items[i]->u.floatValue > value) 
						value = array->items[i]->u.floatValue;
				}
				else 
				{
					value = array->items[i]->u.floatValue;
					hasValue = qtrue;
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

	Plugin_Scr_FreeArray(array);
}

void GScr_LINQ_Cast()
{
	if (Plugin_Scr_GetNumParam() != 2)
	{
		Plugin_Scr_Error("Usage: Cast(<array>, <type>)");
		return;
	}
	VariableValueArray *array = Plugin_Scr_GetArray(0);
	const char *typename = Plugin_Scr_GetString(1);

	Plugin_Scr_MakeArray();
	if (strcasecmp(typename, "string") == 0)
	{
		for (int i = 0; i < array->length; i++)
		{
			switch (array->items[i]->type)
			{
				case VAR_FLOAT:
				{
					int cpyBufferSize = snprintf(NULL, 0, "%f", array->items[i]->u.floatValue);
					char buffer[cpyBufferSize + 1];
					snprintf(buffer, cpyBufferSize + 1, "%f", array->items[i]->u.floatValue);
					Plugin_Scr_AddString(buffer);
					Plugin_Scr_AddArray();
					break;
				}
				case VAR_INTEGER:
				{
					int cpyBufferSize = snprintf(NULL, 0, "%d", array->items[i]->u.intValue);
					char buffer[cpyBufferSize + 1];
					snprintf(buffer, cpyBufferSize + 1, "%d", array->items[i]->u.intValue);
					Plugin_Scr_AddString(buffer);
					Plugin_Scr_AddArray();
					break;
				}
				case VAR_STRING:
				{
					Plugin_Scr_AddVariable(array->items[i]);
					Plugin_Scr_AddArray();
					break;
				}
				case VAR_VECTOR:
				{
					int cpyBufferSize = snprintf(NULL, 0, "(%f, %f, %f)", array->items[i]->u.vectorValue[0],
						array->items[i]->u.vectorValue[1], array->items[i]->u.vectorValue[2]);
					char buffer[cpyBufferSize + 1];
					snprintf(buffer, cpyBufferSize + 1, "(%f, %f, %f)", array->items[i]->u.vectorValue[0],
						array->items[i]->u.vectorValue[1], array->items[i]->u.vectorValue[2]);
					Plugin_Scr_AddString(buffer);
					Plugin_Scr_AddArray();
					break;
				}
			}
		}
	}
	else if (strcasecmp(typename, "int") == 0)
	{
		for (int i = 0; i < array->length; i++)
		{
			switch (array->items[i]->type)
			{
				case VAR_FLOAT:
				{
					Plugin_Scr_AddInt((int)array->items[i]->u.floatValue);
					Plugin_Scr_AddArray();
					break;
				}
				case VAR_INTEGER:
				{
					Plugin_Scr_AddVariable(array->items[i]);
					Plugin_Scr_AddArray();
					break;
				}
				case VAR_STRING:
				{
					const char *nptr = Plugin_SL_ConvertToString(array->items[i]->u.stringValue);
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
	else if (strcasecmp(typename, "float") == 0)
	{
		for (int i = 0; i < array->length; i++)
		{
			switch (array->items[i]->type)
			{
				case VAR_FLOAT:
				{
					Plugin_Scr_AddVariable(array->items[i]);
					Plugin_Scr_AddArray();
					break;
				}
				case VAR_INTEGER:
				{
					Plugin_Scr_AddFloat((float)array->items[i]->u.intValue);
					Plugin_Scr_AddArray();
					break;
				}
				case VAR_STRING:
				{
					const char *nptr = Plugin_SL_ConvertToString(array->items[i]->u.stringValue);
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
	Plugin_Scr_FreeArray(array);
}

void GScr_LINQ_OfType()
{
	if (Plugin_Scr_GetNumParam() != 2)
	{
		Plugin_Scr_Error("Usage: OfType(<array>, <type>)");
		return;
	}
	VariableValueArray *array = Plugin_Scr_GetArray(0);
	const char *typename = Plugin_Scr_GetString(1);

	int reqtype = VAR_UNDEFINED;
	if (strcasecmp(typename, "int") == 0) reqtype = VAR_INTEGER;
	else if (strcasecmp(typename, "float") == 0) reqtype = VAR_FLOAT;
	else if (strcasecmp(typename, "vector") == 0) reqtype = VAR_VECTOR;
	else if (strcasecmp(typename, "array") == 0) reqtype = VAR_ARRAY;
	else if (strcasecmp(typename, "struct") == 0) reqtype = VAR_OBJECT;
	else if (strcasecmp(typename, "string") == 0) reqtype = VAR_STRING;
	else if (strcasecmp(typename, "istring") == 0) reqtype = VAR_ISTRING;
	else if (strcasecmp(typename, "ent") == 0) reqtype = VAR_ENTITY;

	Plugin_Scr_MakeArray();
	for (int i = 0; i < array->length; i++)
	{
		int varType = (array->items[i]->type == VAR_POINTER) 
			? Plugin_Scr_GetObjectType(array->items[i]->u.pointerValue) : array->items[i]->type;
		if (reqtype == varType)
		{
			Plugin_Scr_AddVariable(array->items[i]);
			Plugin_Scr_AddArray();
		}
	}
	Plugin_Scr_FreeArray(array);
}

void GScr_LINQ_Sort()
{
	if (Plugin_Scr_GetNumParam() != 1)
	{
		Plugin_Scr_Error("Usage: Sort(<array>)");
		return;
	}
	VariableValueArray *array = Plugin_Scr_GetArray(0);
	uint32_t flags = Plugin_GetFlagsFromGSCArray(array);

	if (IsFlag(flags, FLAG_FLOAT) || IsFlag(flags, FLAG_INTEGER) || IsFlag(flags, FLAG_STRING)
		|| IsFlag(flags, FLAG_ISTRING) || IsFlag(flags, FLAG_VECTOR))
	{
		Plugin_Scr_MakeArray();
		if (IsFlag(flags, FLAG_FLOAT))
			qsort(array->items, array->length, sizeof(VariableValue *), gsc_float_cmp);
		else if (IsFlag(flags, FLAG_INTEGER))
			qsort(array->items, array->length, sizeof(VariableValue *), gsc_int_cmp);
		else if (IsFlag(flags, FLAG_STRING) || IsFlag(flags, FLAG_ISTRING))
			qsort(array->items, array->length, sizeof(VariableValue *), gsc_cstring_cmp);
		else if (IsFlag(flags, FLAG_VECTOR))
			qsort(array->items, array->length, sizeof(VariableValue *), gsc_vec3_cmp);

		for (int i = 0; i < array->length; i++)
		{
			Plugin_Scr_AddVariable(array->items[i]);
			Plugin_Scr_AddArray();
		}
	}
	else
		Plugin_Scr_AddUndefined();

	Plugin_Scr_FreeArray(array);
}

void GScr_LINQ_Average()
{
	if (Plugin_Scr_GetNumParam() != 1)
	{
		Plugin_Scr_Error("Usage: Average(<array>)");
		return;
	}
	VariableValueArray *array = Plugin_Scr_GetArray(0);
	int count = 0;
	const uint32_t flags = Plugin_GetFlagsFromGSCArray(array);

	if (IsFlag(flags, FLAG_VECTOR))
	{
		vec3_t vec = { 0, 0, 0 };
		for (int i = 0; i < array->length; i++)
		{
			if (array->items[i]->type == VAR_VECTOR)
			{
				vec[0] += array->items[i]->u.vectorValue[0];
				vec[1] += array->items[i]->u.vectorValue[1];
				vec[2] += array->items[i]->u.vectorValue[2];
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
		for (int i = 0; i < array->length; i++)
		{
			if (array->items[i]->type == VAR_FLOAT)
				sum += array->items[i]->u.floatValue;
			else
				sum += array->items[i]->u.intValue;
			count++;
		}
		Plugin_Scr_AddFloat(sum / count);
	}

	Plugin_Scr_FreeArray(array);
}

void GScr_LINQ_Sum()
{
	if (Plugin_Scr_GetNumParam() != 1)
	{
		Plugin_Scr_Error("Usage: Sum(<array>)");
		return;
	}
	VariableValueArray *array = Plugin_Scr_GetArray(0);
	uint32_t flags = Plugin_GetFlagsFromGSCArray(array);

	if (HasFlag(flags, FLAG_STRING) || HasFlag(flags, FLAG_ISTRING))
	{
		unsigned int bufferSize = 1;
		char* buffer = (char*)malloc(sizeof(char));
		for (int i = 0; i < array->length; i++)
		{
			switch (array->items[i]->type)
			{
				case VAR_INTEGER:
				{
					int strSize = snprintf(NULL, 0, "%d", array->items[i]->u.intValue);
					bufferSize += strSize;
					char* temp = (char*)realloc(buffer, bufferSize * sizeof(char));
					if (temp != NULL)
					{
						buffer = temp;
						snprintf(buffer + bufferSize - strSize - 1, bufferSize, "%d", array->items[i]->u.intValue);
					}
				}
				break;
				case VAR_FLOAT:
				{
					int strSize = snprintf(NULL, 0, "%f", array->items[i]->u.floatValue);
					bufferSize += strSize;
					char* temp = (char*)realloc(buffer, bufferSize * sizeof(char));
					if (temp != NULL)
					{
						buffer = temp;
						snprintf(buffer + bufferSize - strSize - 1, bufferSize, "%f", array->items[i]->u.floatValue);
					}
				}
				break;
				case VAR_ISTRING:
				case VAR_STRING:
				{
					const char* gsc_str = Plugin_SL_ConvertToString(array->items[i]->u.stringValue);
					int strSize = snprintf(NULL, 0, "%s", gsc_str);
					bufferSize += strSize;
					char* temp = (char*)realloc(buffer, bufferSize * sizeof(char));
					if (temp != NULL)
					{
						buffer = temp;
						snprintf(buffer + bufferSize - strSize - 1, bufferSize, "%s", gsc_str);
					}
				}
				break;
			}
		}
		Plugin_Scr_AddString(buffer);
		free(buffer);
	}
	else if (HasFlag(flags, FLAG_VECTOR))
	{
		vec3_t sum = { 0, 0, 0 };
		for (int i = 0; i < array->length; i++)
		{
			if (array->items[i]->type == VAR_VECTOR)
			{
				sum[0] += array->items[i]->u.vectorValue[0];
				sum[1] += array->items[i]->u.vectorValue[1];
				sum[2] += array->items[i]->u.vectorValue[2];
			}
		}
		Plugin_Scr_AddVector(sum);
	}
	else if (HasFlag(flags, FLAG_INTEGER) || HasFlag(flags, FLAG_FLOAT))
	{
		float sum = 0;
		for (int i = 0; i < array->length; i++)
		{
			switch (array->items[i]->type)
			{
				case VAR_INTEGER: sum += array->items[i]->u.intValue; break;
				case VAR_FLOAT: sum += array->items[i]->u.floatValue; break;
			}
		}
		if (!HasFlag(flags, FLAG_FLOAT))
			Plugin_Scr_AddInt((int)sum);
		else
			Plugin_Scr_AddFloat(sum);
	}
	else
		Plugin_Scr_AddUndefined();

	Plugin_Scr_FreeArray(array);
}

void GScr_LINQ_Range()
{
	if (Plugin_Scr_GetNumParam() != 3)
	{
		Plugin_Scr_Error("Usage: Range(<array>, <min>, <max>)");
		return;
	}
	VariableValueArray *array = Plugin_Scr_GetArray(0);
	const uint32_t min = Plugin_Scr_GetInt(1);
	const uint32_t max = Plugin_Scr_GetInt(2);

	if (min >= max || max < min)
	{
		Plugin_Scr_Error("Range() - wrong min/max value");
		return;
	}

	Plugin_Scr_MakeArray();
	for (int i = min; i < max; i++)
	{
		Plugin_Scr_AddVariable(array->items[i]);
		Plugin_Scr_AddArray();
	}
	Plugin_Scr_FreeArray(array);
}

void GScr_LINQ_Repeat()
{
	if (Plugin_Scr_GetNumParam() != 2)
	{
		Plugin_Scr_Error("Usage: Repeat(<array>, <count>)");
		return;
	}
	VariableValueArray *array = Plugin_Scr_GetArray(0);
	const uint32_t count = Plugin_Scr_GetInt(1);

	Plugin_Scr_MakeArray();
	for (int r = 0; r < count; r++)
	{
		for (int i = 0; i < array->length; i++)
		{
			Plugin_Scr_AddVariable(array->items[i]);
			Plugin_Scr_AddArray();
		}
	}
	Plugin_Scr_FreeArray(array);
}
