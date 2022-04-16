#include "enumerables.h"
#include "utils/stringutils.h"
#include "utils/polycmp.h"
#include "utils/utils.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void GScr_LINQ_Reverse()
{
	CHECK_PARAMS(1, "Usage: Reverse(<array>)");

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
	CHECK_PARAMS(1, "Usage: Min(<array>)");

	VariableValueArray *array = Plugin_Scr_GetArray(0);
	int flags = Plugin_Scr_GetArrayFlags(array);

	if (!array->length)
	{
		Plugin_Scr_FreeArray(array);
		return;
	}

	if (HasFlag(flags, FLAG_STRING) || HasFlag(flags, FLAG_ISTRING))
		Scr_StringMin(array);
	else if (HasFlag(flags, FLAG_VECTOR))
		Scr_VectorMin(array);
	else if (HasFlag(flags, FLAG_INTEGER) || HasFlag(flags, FLAG_FLOAT))
		Scr_NumberMin(array, flags);
	Plugin_Scr_FreeArray(array);
}

void Scr_StringMin(VariableValueArray* array)
{
	char* result = (char *)Plugin_SL_ConvertToString(array->items[0]->u.stringValue);
	int currentLength = strlen(result);

	for (int i = 1; i < array->length; i++)
	{
		char* value = (char*)Plugin_SL_ConvertToString(array->items[i]->u.stringValue);
		int length = strlen(value);

		if (length < currentLength)
		{
			currentLength = length;
			result = value;
		}
	}
	Plugin_Scr_AddString(result);
}

void Scr_VectorMin(VariableValueArray* array)
{
	vec3_t zero = { 0, 0, 0 };
	float* result = (float*)array->items[0]->u.vectorValue;
	float currentDistance = VectorDistance(result, zero);

	for (int i = 1; i < array->length; i++)
	{
		float* value = (float*)array->items[i]->u.vectorValue;
		float distance = VectorDistance(value, zero);

		if (distance < currentDistance)
		{
			currentDistance = distance;
			result = value;
		}
	}
	Plugin_Scr_AddVector(result);
}

void Scr_NumberMin(VariableValueArray* array, int flags)
{
	float result = array->items[0]->type == VAR_INTEGER
		? array->items[0]->u.intValue
		: array->items[0]->u.floatValue;

	for (int i = 1; i < array->length; i++)
	{
		if (array->items[i]->type == VAR_INTEGER)
		{
			if (array->items[i]->u.intValue < result)
				result = array->items[i]->u.intValue;
		}
		else if (array->items[i]->type == VAR_FLOAT)
		{
			if (array->items[i]->u.floatValue < result)
				result = array->items[i]->u.floatValue;
		}
	}
	if (!HasFlag(flags, FLAG_FLOAT))
		Plugin_Scr_AddInt((int)result);
	else
		Plugin_Scr_AddFloat(result);
}

void GScr_LINQ_Max()
{
	CHECK_PARAMS(1, "Usage: Max(<array>)");

	VariableValueArray *array = Plugin_Scr_GetArray(0);
	uint32_t flags = Plugin_Scr_GetArrayFlags(array);

	if (!array->length)
	{
		Plugin_Scr_FreeArray(array);
		return;
	}

	if (HasFlag(flags, FLAG_STRING) || HasFlag(flags, FLAG_ISTRING))
		Scr_StringMax(array);
	else if (HasFlag(flags, FLAG_VECTOR))
		Scr_VectorMax(array);
	else if (HasFlag(flags, FLAG_INTEGER) || HasFlag(flags, FLAG_FLOAT))
		Scr_NumberMax(array, flags);
	Plugin_Scr_FreeArray(array);
}

void Scr_StringMax(VariableValueArray* array)
{
	char* result = (char *)Plugin_SL_ConvertToString(array->items[0]->u.stringValue);
	int currentLength = strlen(result);

	for (int i = 1; i < array->length; i++)
	{
		char* value = (char*)Plugin_SL_ConvertToString(array->items[i]->u.stringValue);
		int length = strlen(value);

		if (length > currentLength)
		{
			currentLength = length;
			result = value;
		}
	}
	Plugin_Scr_AddString(result);
}

void Scr_VectorMax(VariableValueArray* array)
{
	vec3_t zero = { 0, 0, 0 };
	float* result = (float*)array->items[0]->u.vectorValue;
	float currentDistance = VectorDistance(result, zero);

	for (int i = 1; i < array->length; i++)
	{
		float* value = (float*)array->items[i]->u.vectorValue;
		float distance = VectorDistance(value, zero);

		if (distance > currentDistance)
		{
			currentDistance = distance;
			result = value;
		}
	}
	Plugin_Scr_AddVector(result);
}

void Scr_NumberMax(VariableValueArray* array, int flags)
{
	float result = array->items[0]->type == VAR_INTEGER
		? array->items[0]->u.intValue
		: array->items[0]->u.floatValue;

	for (int i = 0; i < array->length; i++)
	{
		if (array->items[i]->type == VAR_INTEGER)
		{
			if (array->items[i]->u.intValue > result)
				result = array->items[i]->u.intValue;
		}
		else if (array->items[i]->type == VAR_FLOAT)
		{
			if (array->items[i]->u.floatValue > result)
				result = array->items[i]->u.floatValue;
		}
	}
	if (!HasFlag(flags, FLAG_FLOAT))
		Plugin_Scr_AddInt((int)result);
	else
		Plugin_Scr_AddFloat(result);
}

void GScr_LINQ_Cast()
{
	CHECK_PARAMS(2, "Usage: Cast(<array>, <type>)");

	VariableValueArray *array = Plugin_Scr_GetArray(0);
	const char *typename = Plugin_Scr_GetString(1);

	Plugin_Scr_MakeArray();
	if (strcasecmp(typename, "string") == 0)
		Scr_StringCast(array);
	else if (strcasecmp(typename, "int") == 0)
		Scr_IntCast(array);
	else if (strcasecmp(typename, "float") == 0)
		Scr_FloatCast(array);
	Plugin_Scr_FreeArray(array);
}

void Scr_StringCast(VariableValueArray *array)
{
	for (int i = 0; i < array->length; i++)
	{
		switch (array->items[i]->type)
		{
			case VAR_FLOAT:
			{
				Plugin_Scr_AddString(fmt("%f", array->items[i]->u.floatValue));
				Plugin_Scr_AddArray();
				break;
			}
			case VAR_INTEGER:
			{
				Plugin_Scr_AddString(fmt("%d", array->items[i]->u.intValue));
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
				Plugin_Scr_AddString(fmt("(%f, %f, %f)",
					array->items[i]->u.vectorValue[0],
					array->items[i]->u.vectorValue[1],
					array->items[i]->u.vectorValue[2]));
				Plugin_Scr_AddArray();
				break;
			}
		}
	}
}

void Scr_IntCast(VariableValueArray* array)
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
				const char* nptr = Plugin_SL_ConvertToString(array->items[i]->u.stringValue);
				char* endptr = NULL;
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

void Scr_FloatCast(VariableValueArray* array)
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
				const char* nptr = Plugin_SL_ConvertToString(array->items[i]->u.stringValue);
				char* endptr = NULL;
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

void GScr_LINQ_OfType()
{
	CHECK_PARAMS(2, "Usage: OfType(<array>, <type>)");

	VariableValueArray *array = Plugin_Scr_GetArray(0);
	const char *typename = Plugin_Scr_GetString(1);

	int ofType = VAR_UNDEFINED;
	if (strcasecmp(typename, "int") == 0) 
		ofType = VAR_INTEGER;
	else if (strcasecmp(typename, "float") == 0) 
		ofType = VAR_FLOAT;
	else if (strcasecmp(typename, "vector") == 0) 
		ofType = VAR_VECTOR;
	else if (strcasecmp(typename, "array") == 0) 
		ofType = VAR_ARRAY;
	else if (strcasecmp(typename, "struct") == 0) 
		ofType = VAR_OBJECT;
	else if (strcasecmp(typename, "string") == 0) 
		ofType = VAR_STRING;
	else if (strcasecmp(typename, "istring") == 0) 
		ofType = VAR_ISTRING;
	else if (strcasecmp(typename, "ent") == 0) 
		ofType = VAR_ENTITY;

	Plugin_Scr_MakeArray();
	for (int i = 0; i < array->length; i++)
	{
		int type = (array->items[i]->type == VAR_POINTER)
			? Plugin_Scr_GetObjectType(array->items[i]->u.pointerValue) 
			: array->items[i]->type;
		if (ofType == type)
		{
			Plugin_Scr_AddVariable(array->items[i]);
			Plugin_Scr_AddArray();
		}
	}
	Plugin_Scr_FreeArray(array);
}

void GScr_LINQ_Sort()
{
	CHECK_PARAMS(1, "Usage: Sort(<array>)");

	VariableValueArray *array = Plugin_Scr_GetArray(0);
	uint32_t flags = Plugin_Scr_GetArrayFlags(array);

	Plugin_Scr_MakeArray();
	if (IsFlag(flags, FLAG_FLOAT))
		qsort(array->items, array->length, sizeof(VariableValue *), Scr_FloatCmp);
	else if (IsFlag(flags, FLAG_INTEGER))
		qsort(array->items, array->length, sizeof(VariableValue *), Scr_IntCmp);
	else if (IsFlag(flags, FLAG_STRING) || IsFlag(flags, FLAG_ISTRING))
		qsort(array->items, array->length, sizeof(VariableValue *), Scr_StringCmp);
	else if (IsFlag(flags, FLAG_VECTOR))
		qsort(array->items, array->length, sizeof(VariableValue *), Scr_VectorCmp);

	for (int i = 0; i < array->length; i++)
	{
		Plugin_Scr_AddVariable(array->items[i]);
		Plugin_Scr_AddArray();
	}
	Plugin_Scr_FreeArray(array);
}

void GScr_LINQ_Average()
{
	CHECK_PARAMS(1, "Usage: Average(<array>)");

	VariableValueArray *array = Plugin_Scr_GetArray(0);
	const uint32_t flags = Plugin_Scr_GetArrayFlags(array);

	if (IsFlag(flags, FLAG_VECTOR))
		Scr_VectorAverage(array);
	else if (IsFlag(flags, FLAG_INTEGER) || IsFlag(flags, FLAG_FLOAT))
		Scr_NumberAverage(array, flags);
	Plugin_Scr_FreeArray(array);
}

void Scr_VectorAverage(VariableValueArray* array)
{
	int count = 0;
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

void Scr_NumberAverage(VariableValueArray* array, int flags)
{
	int count = 0;
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

void GScr_LINQ_Sum()
{
	CHECK_PARAMS(1, "Usage: Sum(<array>)");

	VariableValueArray *array = Plugin_Scr_GetArray(0);
	uint32_t flags = Plugin_Scr_GetArrayFlags(array);

	if (HasFlag(flags, FLAG_STRING) || HasFlag(flags, FLAG_ISTRING))
		Scr_StringSum(array);
	else if (HasFlag(flags, FLAG_VECTOR))
		Scr_VectorSum(array);
	else if (HasFlag(flags, FLAG_INTEGER) || HasFlag(flags, FLAG_FLOAT))
		Scr_NumberSum(array, flags);
	Plugin_Scr_FreeArray(array);
}

void Scr_StringSum(VariableValueArray* array)
{
	char result[MAX_STRING_CHARS] = { 0 };
	for (int i = 0; i < array->length; i++)
	{
		switch (array->items[i]->type)
		{
		case VAR_INTEGER:
			strcat(result, fmt("%d", array->items[i]->u.intValue));
			break;
		case VAR_FLOAT:
			strcat(result, fmt("%f", array->items[i]->u.floatValue));
			break;
		case VAR_ISTRING:
		case VAR_STRING:
			strcat(result, fmt("%s", Plugin_SL_ConvertToString(array->items[i]->u.stringValue)));
			break;
		}
	}
	Plugin_Scr_AddString(result);
}

void Scr_VectorSum(VariableValueArray* array)
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

void Scr_NumberSum(VariableValueArray* array, int flags)
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

void GScr_LINQ_Range()
{
	CHECK_PARAMS(3, "Usage: Range(<array>, <min>, <max>)");

	VariableValueArray *array = Plugin_Scr_GetArray(0);
	const int min = Plugin_Scr_GetInt(1);
	const int max = Plugin_Scr_GetInt(2);

	if (min >= max || max < min)
	{
		Plugin_Scr_Error("Range() - Wrong min/max value");
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
	CHECK_PARAMS(2, "Usage: Repeat(<array>, <count>)");

	VariableValueArray *array = Plugin_Scr_GetArray(0);
	const int count = Plugin_Scr_GetInt(1);

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

void GScr_LINQ_Concat()
{
	CHECK_PARAMS(2, "Usage: Repeat(<arraySource>, <array>)");

	VariableValueArray* arraySource = Plugin_Scr_GetArray(0);
	VariableValueArray* array = Plugin_Scr_GetArray(1);

	Plugin_Scr_MakeArray();
	for (int i = 0; i < arraySource->length; i++)
	{
		Plugin_Scr_AddVariable(arraySource->items[i]);
		Plugin_Scr_AddArray();
	}
	for (int i = 0; i < array->length; i++)
	{
		Plugin_Scr_AddVariable(array->items[i]);
		Plugin_Scr_AddArray();
	}
	Plugin_Scr_FreeArray(array);
}
