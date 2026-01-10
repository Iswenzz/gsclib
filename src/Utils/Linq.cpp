#include "Linq.hpp"
#include "Utils.hpp"

#include <algorithm>
#include <charconv>
#include <cstring>

namespace gsclib
{
	void Linq::Select()
	{
		CHECK_PARAMS(2, "Usage: Select(<array>, <::delegate>)\n");

		VariableValueArray array = Plugin_Scr_GetArray(0);
		const int threadId = Plugin_Scr_GetFunc(1);

		Plugin_Scr_MakeArray();
		for (int i = 0; i < array.length; i++)
		{
			Plugin_Scr_AddInt(i);
			Plugin_Scr_AddVariable(array.items[i]);

			const short tid = Plugin_Scr_ExecThreadResult(threadId, 2);
			VariableValue var = Plugin_Scr_GetThreadResult();

			Plugin_Scr_AddVariable(var);
			Plugin_Scr_AddArray();
			Plugin_Scr_FreeThread(tid);
		}
		Plugin_Scr_FreeArray(&array);
	}

	void Linq::Foreach()
	{
		CHECK_PARAMS(2, "Usage: Foreach(<array>, <::delegate>)\n");

		VariableValueArray array = Plugin_Scr_GetArray(0);
		const int threadId = Plugin_Scr_GetFunc(1);

		for (int i = 0; i < array.length; i++)
		{
			Plugin_Scr_AddInt(i);
			Plugin_Scr_AddVariable(array.items[i]);
			const short tid = Plugin_Scr_ExecThreadResult(threadId, 2);
			Plugin_Scr_FreeThread(tid);
		}
		Plugin_Scr_FreeArray(&array);
	}

	void Linq::Aggregate()
	{
		CHECK_PARAMS(3, "Usage: Aggregate(<initialValue>, <array>, <::delegate>)\n");

		VariableValue previousValue = *Plugin_Scr_SelectParam(0);
		VariableValueArray array = Plugin_Scr_GetArray(1);
		const int threadId = Plugin_Scr_GetFunc(2);

		for (int i = 0; i < array.length; i++)
		{
			Plugin_Scr_AddInt(i);
			Plugin_Scr_AddVariable(array.items[i]);
			Plugin_Scr_AddVariable(previousValue);
			const short tid = Plugin_Scr_ExecThreadResult(threadId, 3);
			previousValue = Plugin_Scr_GetThreadResult();
			Plugin_Scr_FreeThread(tid);
		}
		Plugin_Scr_FreeArray(&array);
		Plugin_Scr_AddVariable(previousValue);
	}

	void Linq::All()
	{
		CHECK_PARAMS(2, "Usage: All(<array>, <::predicate>)\n");

		VariableValueArray array = Plugin_Scr_GetArray(0);
		const int threadId = Plugin_Scr_GetFunc(1);
		qboolean result = qtrue;

		for (int i = 0; i < array.length; i++)
		{
			Plugin_Scr_AddInt(i);
			Plugin_Scr_AddVariable(array.items[i]);
			const short tid = Plugin_Scr_ExecThread(threadId, 2);

			if (!Plugin_Scr_GetThreadResult().u.intValue)
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

	void Linq::Any()
	{
		CHECK_PARAMS(2, "Usage: Any(<array>, <::predicate>)\n");

		VariableValueArray array = Plugin_Scr_GetArray(0);
		const int threadId = Plugin_Scr_GetFunc(1);
		qboolean result = qfalse;

		for (int i = 0; i < array.length; i++)
		{
			Plugin_Scr_AddInt(i);
			Plugin_Scr_AddVariable(array.items[i]);
			const short tid = Plugin_Scr_ExecThread(threadId, 2);

			if (Plugin_Scr_GetThreadResult().u.intValue)
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

	void Linq::Where()
	{
		CHECK_PARAMS(2, "Usage: Where(<array>, <::predicate>)\n");

		VariableValueArray array = Plugin_Scr_GetArray(0);
		const int threadId = Plugin_Scr_GetFunc(1);

		Plugin_Scr_MakeArray();
		for (int i = 0; i < array.length; i++)
		{
			Plugin_Scr_AddInt(i);
			Plugin_Scr_AddVariable(array.items[i]);
			const short tid = Plugin_Scr_ExecThread(threadId, 2);

			if (Plugin_Scr_GetThreadResult().u.intValue)
			{
				Plugin_Scr_AddVariable(array.items[i]);
				Plugin_Scr_AddArray();
			}
			Plugin_Scr_FreeThread(tid);
		}
		Plugin_Scr_FreeArray(&array);
	}

	void Linq::Last()
	{
		CHECK_PARAMS(2, "Usage: Last(<array>, <::predicate>)\n");

		VariableValueArray array = Plugin_Scr_GetArray(0);
		const int threadId = Plugin_Scr_GetFunc(1);
		VariableValue* last = nullptr;

		for (int i = 0; i < array.length; i++)
		{
			Plugin_Scr_AddInt(i);
			Plugin_Scr_AddVariable(array.items[i]);
			const short tid = Plugin_Scr_ExecThread(threadId, 2);

			if (Plugin_Scr_GetThreadResult().u.intValue)
				last = &array.items[i];
			Plugin_Scr_FreeThread(tid);
		}
		if (last != nullptr)
			Plugin_Scr_AddVariable(*last);
		Plugin_Scr_FreeArray(&array);
	}

	void Linq::First()
	{
		CHECK_PARAMS(2, "Usage: First(<array>, <::predicate>)\n");

		VariableValueArray array = Plugin_Scr_GetArray(0);
		const int threadId = Plugin_Scr_GetFunc(1);

		for (int i = 0; i < array.length; i++)
		{
			Plugin_Scr_AddInt(i);
			Plugin_Scr_AddVariable(array.items[i]);
			const short tid = Plugin_Scr_ExecThread(threadId, 2);

			if (Plugin_Scr_GetThreadResult().u.intValue)
			{
				Plugin_Scr_AddVariable(array.items[i]);
				Plugin_Scr_FreeThread(tid);
				break;
			}
			Plugin_Scr_FreeThread(tid);
		}
		Plugin_Scr_FreeArray(&array);
	}

	void Linq::Count()
	{
		CHECK_PARAMS(2, "Usage: Count(<array>, <::predicate>)\n");

		VariableValueArray array = Plugin_Scr_GetArray(0);
		const int threadId = Plugin_Scr_GetFunc(1);
		int result = 0;

		for (int i = 0; i < array.length; i++)
		{
			Plugin_Scr_AddInt(i);
			Plugin_Scr_AddVariable(array.items[i]);
			const short tid = Plugin_Scr_ExecThread(threadId, 2);

			if (Plugin_Scr_GetThreadResult().u.intValue)
				result++;

			Plugin_Scr_FreeThread(tid);
		}
		Plugin_Scr_FreeArray(&array);
		Plugin_Scr_AddInt(result);
	}

	void Linq::Reverse()
	{
		CHECK_PARAMS(1, "Usage: Reverse(<array>)\n");

		VariableValueArray array = Plugin_Scr_GetArray(0);
		Plugin_Scr_MakeArray();

		for (int i = array.length - 1; i > -1; i--)
		{
			Plugin_Scr_AddVariable(array.items[i]);
			Plugin_Scr_AddArray();
		}
		Plugin_Scr_FreeArray(&array);
	}

	void Linq::Min()
	{
		CHECK_PARAMS(1, "Usage: Min(<array>)\n");

		VariableValueArray array = Plugin_Scr_GetArray(0);
		int flags = Plugin_Scr_GetArrayFlags(array);

		if (!array.length)
		{
			Plugin_Scr_FreeArray(&array);
			return;
		}
		if (Utils::HasFlag(flags, FLAG_STRING) || Utils::HasFlag(flags, FLAG_ISTRING))
			StringMin(array);
		else if (Utils::HasFlag(flags, FLAG_VECTOR))
			VectorMin(array);
		else if (Utils::HasFlag(flags, FLAG_INTEGER) || Utils::HasFlag(flags, FLAG_FLOAT))
			NumberMin(array, flags);
		Plugin_Scr_FreeArray(&array);
	}

	void Linq::StringMin(VariableValueArray array)
	{
		const char* result = Plugin_SL_ConvertToString(array.items[0].u.stringValue);
		size_t currentLength = std::string_view(result).size();

		for (int i = 1; i < array.length; i++)
		{
			const char* value = Plugin_SL_ConvertToString(array.items[i].u.stringValue);
			size_t length = std::string_view(value).size();

			if (length < currentLength)
			{
				currentLength = length;
				result = value;
			}
		}
		Plugin_Scr_AddString(result);
	}

	void Linq::VectorMin(VariableValueArray array)
	{
		vec3_t zero = { 0, 0, 0 };
		const float* result = array.items[0].u.vectorValue;
		float currentDistance = Utils::VectorDistance(result, zero);

		for (int i = 1; i < array.length; i++)
		{
			const float* value = array.items[i].u.vectorValue;
			float distance = Utils::VectorDistance(value, zero);

			if (distance < currentDistance)
			{
				currentDistance = distance;
				result = value;
			}
		}
		vec3_t vec = { result[0], result[1], result[2] };
		Plugin_Scr_AddVector(vec);
	}

	void Linq::NumberMin(VariableValueArray array, int flags)
	{
		float result = array.items[0].type == VAR_INTEGER ? static_cast<float>(array.items[0].u.intValue)
														  : array.items[0].u.floatValue;

		for (int i = 1; i < array.length; i++)
		{
			if (array.items[i].type == VAR_INTEGER)
			{
				if (array.items[i].u.intValue < result)
					result = static_cast<float>(array.items[i].u.intValue);
			}
			else if (array.items[i].type == VAR_FLOAT)
			{
				if (array.items[i].u.floatValue < result)
					result = array.items[i].u.floatValue;
			}
		}
		if (!Utils::HasFlag(flags, FLAG_FLOAT))
			Plugin_Scr_AddInt(static_cast<int>(result));
		else
			Plugin_Scr_AddFloat(result);
	}

	void Linq::Max()
	{
		CHECK_PARAMS(1, "Usage: Max(<array>)\n");

		VariableValueArray array = Plugin_Scr_GetArray(0);
		uint32_t flags = Plugin_Scr_GetArrayFlags(array);

		if (!array.length)
		{
			Plugin_Scr_FreeArray(&array);
			return;
		}
		if (Utils::HasFlag(flags, FLAG_STRING) || Utils::HasFlag(flags, FLAG_ISTRING))
			StringMax(array);
		else if (Utils::HasFlag(flags, FLAG_VECTOR))
			VectorMax(array);
		else if (Utils::HasFlag(flags, FLAG_INTEGER) || Utils::HasFlag(flags, FLAG_FLOAT))
			NumberMax(array, flags);
		Plugin_Scr_FreeArray(&array);
	}

	void Linq::StringMax(VariableValueArray array)
	{
		const char* result = Plugin_SL_ConvertToString(array.items[0].u.stringValue);
		size_t currentLength = std::string_view(result).size();

		for (int i = 1; i < array.length; i++)
		{
			const char* value = Plugin_SL_ConvertToString(array.items[i].u.stringValue);
			size_t length = std::string_view(value).size();

			if (length > currentLength)
			{
				currentLength = length;
				result = value;
			}
		}
		Plugin_Scr_AddString(result);
	}

	void Linq::VectorMax(VariableValueArray array)
	{
		vec3_t zero = { 0, 0, 0 };
		const float* result = array.items[0].u.vectorValue;
		float currentDistance = Utils::VectorDistance(result, zero);

		for (int i = 1; i < array.length; i++)
		{
			const float* value = array.items[i].u.vectorValue;
			float distance = Utils::VectorDistance(value, zero);

			if (distance > currentDistance)
			{
				currentDistance = distance;
				result = value;
			}
		}
		vec3_t vec = { result[0], result[1], result[2] };
		Plugin_Scr_AddVector(vec);
	}

	void Linq::NumberMax(VariableValueArray array, int flags)
	{
		float result = array.items[0].type == VAR_INTEGER ? static_cast<float>(array.items[0].u.intValue)
														  : array.items[0].u.floatValue;

		for (int i = 0; i < array.length; i++)
		{
			if (array.items[i].type == VAR_INTEGER)
			{
				if (array.items[i].u.intValue > result)
					result = static_cast<float>(array.items[i].u.intValue);
			}
			else if (array.items[i].type == VAR_FLOAT)
			{
				if (array.items[i].u.floatValue > result)
					result = array.items[i].u.floatValue;
			}
		}
		if (!Utils::HasFlag(flags, FLAG_FLOAT))
			Plugin_Scr_AddInt(static_cast<int>(result));
		else
			Plugin_Scr_AddFloat(result);
	}

	void Linq::Cast()
	{
		CHECK_PARAMS(2, "Usage: Cast(<array>, <type>)\n");

		VariableValueArray array = Plugin_Scr_GetArray(0);
		std::string_view typeName = Plugin_Scr_GetString(1);

		Plugin_Scr_MakeArray();
		if (typeName == "string")
			StringCast(array);
		else if (typeName == "int")
			IntCast(array);
		else if (typeName == "float")
			FloatCast(array);
		Plugin_Scr_FreeArray(&array);
	}

	void Linq::StringCast(VariableValueArray array)
	{
		for (int i = 0; i < array.length; i++)
		{
			switch (array.items[i].type)
			{
			case VAR_FLOAT:
				Plugin_Scr_AddString(std::format("{}", array.items[i].u.floatValue).c_str());
				Plugin_Scr_AddArray();
				break;
			case VAR_INTEGER:
				Plugin_Scr_AddString(std::format("{}", array.items[i].u.intValue).c_str());
				Plugin_Scr_AddArray();
				break;
			case VAR_STRING:
				Plugin_Scr_AddVariable(array.items[i]);
				Plugin_Scr_AddArray();
				break;
			case VAR_VECTOR:
				Plugin_Scr_AddString(std::format("({}, {}, {})", array.items[i].u.vectorValue[0],
					array.items[i].u.vectorValue[1], array.items[i].u.vectorValue[2])
										 .c_str());
				Plugin_Scr_AddArray();
				break;
			}
		}
	}

	void Linq::IntCast(VariableValueArray array)
	{
		for (int i = 0; i < array.length; i++)
		{
			switch (array.items[i].type)
			{
			case VAR_FLOAT:
				Plugin_Scr_AddInt(static_cast<int>(array.items[i].u.floatValue));
				Plugin_Scr_AddArray();
				break;
			case VAR_INTEGER:
				Plugin_Scr_AddVariable(array.items[i]);
				Plugin_Scr_AddArray();
				break;
			case VAR_STRING:
			{
				const char* str = Plugin_SL_ConvertToString(array.items[i].u.stringValue);
				std::string_view sv(str);
				int number = 0;
				auto [ptr, ec] = std::from_chars(sv.data(), sv.data() + sv.size(), number);

				if (ec == std::errc() && ptr == sv.data() + sv.size())
				{
					Plugin_Scr_AddInt(number);
					Plugin_Scr_AddArray();
				}
				break;
			}
			}
		}
	}

	void Linq::FloatCast(VariableValueArray array)
	{
		for (int i = 0; i < array.length; i++)
		{
			switch (array.items[i].type)
			{
			case VAR_FLOAT:
				Plugin_Scr_AddVariable(array.items[i]);
				Plugin_Scr_AddArray();
				break;
			case VAR_INTEGER:
				Plugin_Scr_AddFloat(static_cast<float>(array.items[i].u.intValue));
				Plugin_Scr_AddArray();
				break;
			case VAR_STRING:
			{
				const char* str = Plugin_SL_ConvertToString(array.items[i].u.stringValue);
				std::string_view sv(str);
				float number = 0.0f;
				auto [ptr, ec] = std::from_chars(sv.data(), sv.data() + sv.size(), number);

				if (ec == std::errc() && ptr == sv.data() + sv.size())
				{
					Plugin_Scr_AddFloat(number);
					Plugin_Scr_AddArray();
				}
				break;
			}
			}
		}
	}

	void Linq::OfType()
	{
		CHECK_PARAMS(2, "Usage: OfType(<array>, <type>)\n");

		VariableValueArray array = Plugin_Scr_GetArray(0);
		std::string_view typeName = Plugin_Scr_GetString(1);

		int ofType = VAR_UNDEFINED;
		if (typeName == "int")
			ofType = VAR_INTEGER;
		else if (typeName == "float")
			ofType = VAR_FLOAT;
		else if (typeName == "vector")
			ofType = VAR_VECTOR;
		else if (typeName == "array")
			ofType = VAR_ARRAY;
		else if (typeName == "struct")
			ofType = VAR_OBJECT;
		else if (typeName == "string")
			ofType = VAR_STRING;
		else if (typeName == "istring")
			ofType = VAR_ISTRING;
		else if (typeName == "ent")
			ofType = VAR_ENTITY;

		Plugin_Scr_MakeArray();
		for (int i = 0; i < array.length; i++)
		{
			int type = (array.items[i].type == VAR_POINTER) ? Plugin_Scr_GetObjectType(array.items[i].u.pointerValue)
															: array.items[i].type;
			if (ofType == type)
			{
				Plugin_Scr_AddVariable(array.items[i]);
				Plugin_Scr_AddArray();
			}
		}
		Plugin_Scr_FreeArray(&array);
	}

	void Linq::Sort()
	{
		CHECK_PARAMS(1, "Usage: Sort(<array>)\n");

		VariableValueArray array = Plugin_Scr_GetArray(0);
		uint32_t flags = Plugin_Scr_GetArrayFlags(array);

		Plugin_Scr_MakeArray();
		if (Utils::IsFlag(flags, FLAG_FLOAT))
			std::qsort(array.items, array.length, sizeof(VariableValue), Utils::FloatCmp);
		else if (Utils::IsFlag(flags, FLAG_INTEGER))
			std::qsort(array.items, array.length, sizeof(VariableValue), Utils::IntCmp);
		else if (Utils::IsFlag(flags, FLAG_STRING) || Utils::IsFlag(flags, FLAG_ISTRING))
			std::qsort(array.items, array.length, sizeof(VariableValue), Utils::StringCmp);
		else if (Utils::IsFlag(flags, FLAG_VECTOR))
			std::qsort(array.items, array.length, sizeof(VariableValue), Utils::VectorCmp);

		for (int i = 0; i < array.length; i++)
		{
			Plugin_Scr_AddVariable(array.items[i]);
			Plugin_Scr_AddArray();
		}
		Plugin_Scr_FreeArray(&array);
	}

	void Linq::Average()
	{
		CHECK_PARAMS(1, "Usage: Average(<array>)\n");

		VariableValueArray array = Plugin_Scr_GetArray(0);
		const uint32_t flags = Plugin_Scr_GetArrayFlags(array);

		if (Utils::IsFlag(flags, FLAG_VECTOR))
			VectorAverage(array);
		else if (Utils::IsFlag(flags, FLAG_INTEGER) || Utils::IsFlag(flags, FLAG_FLOAT))
			NumberAverage(array, flags);
		Plugin_Scr_FreeArray(&array);
	}

	void Linq::VectorAverage(VariableValueArray array)
	{
		int count = 0;
		vec3_t vec = { 0, 0, 0 };

		for (int i = 0; i < array.length; i++)
		{
			if (array.items[i].type == VAR_VECTOR)
			{
				vec[0] += array.items[i].u.vectorValue[0];
				vec[1] += array.items[i].u.vectorValue[1];
				vec[2] += array.items[i].u.vectorValue[2];
				count++;
			}
		}
		vec[0] /= count;
		vec[1] /= count;
		vec[2] /= count;

		Plugin_Scr_AddVector(vec);
	}

	void Linq::NumberAverage(VariableValueArray array, int flags)
	{
		int count = 0;
		float sum = 0;

		for (int i = 0; i < array.length; i++)
		{
			if (array.items[i].type == VAR_FLOAT)
				sum += array.items[i].u.floatValue;
			else
				sum += array.items[i].u.intValue;
			count++;
		}
		Plugin_Scr_AddFloat(sum / count);
	}

	void Linq::Sum()
	{
		CHECK_PARAMS(1, "Usage: Sum(<array>)\n");

		VariableValueArray array = Plugin_Scr_GetArray(0);
		uint32_t flags = Plugin_Scr_GetArrayFlags(array);

		if (Utils::HasFlag(flags, FLAG_STRING) || Utils::HasFlag(flags, FLAG_ISTRING))
			StringSum(array);
		else if (Utils::HasFlag(flags, FLAG_VECTOR))
			VectorSum(array);
		else if (Utils::HasFlag(flags, FLAG_INTEGER) || Utils::HasFlag(flags, FLAG_FLOAT))
			NumberSum(array, flags);
		Plugin_Scr_FreeArray(&array);
	}

	void Linq::StringSum(VariableValueArray array)
	{
		std::string result;
		for (int i = 0; i < array.length; i++)
		{
			switch (array.items[i].type)
			{
			case VAR_INTEGER:
				result += std::format("{}", array.items[i].u.intValue);
				break;
			case VAR_FLOAT:
				result += std::format("{}", array.items[i].u.floatValue);
				break;
			case VAR_ISTRING:
			case VAR_STRING:
				result += Plugin_SL_ConvertToString(array.items[i].u.stringValue);
				break;
			}
		}
		Plugin_Scr_AddString(result.c_str());
	}

	void Linq::VectorSum(VariableValueArray array)
	{
		vec3_t sum = { 0, 0, 0 };
		for (int i = 0; i < array.length; i++)
		{
			if (array.items[i].type == VAR_VECTOR)
			{
				sum[0] += array.items[i].u.vectorValue[0];
				sum[1] += array.items[i].u.vectorValue[1];
				sum[2] += array.items[i].u.vectorValue[2];
			}
		}
		Plugin_Scr_AddVector(sum);
	}

	void Linq::NumberSum(VariableValueArray array, int flags)
	{
		float sum = 0;
		for (int i = 0; i < array.length; i++)
		{
			switch (array.items[i].type)
			{
			case VAR_INTEGER:
				sum += array.items[i].u.intValue;
				break;
			case VAR_FLOAT:
				sum += array.items[i].u.floatValue;
				break;
			}
		}
		if (!Utils::HasFlag(flags, FLAG_FLOAT))
			Plugin_Scr_AddInt(static_cast<int>(sum));
		else
			Plugin_Scr_AddFloat(sum);
	}

	void Linq::Range()
	{
		CHECK_PARAMS(3, "Usage: Range(<array>, <min>, <max>)\n");

		VariableValueArray array = Plugin_Scr_GetArray(0);
		const int min = Plugin_Scr_GetInt(1);
		const int max = Plugin_Scr_GetInt(2);

		if (min >= max || max < min)
		{
			Plugin_Scr_Error("Range() - Wrong min/max value\n");
			return;
		}

		Plugin_Scr_MakeArray();
		for (int i = min; i < max; i++)
		{
			Plugin_Scr_AddVariable(array.items[i]);
			Plugin_Scr_AddArray();
		}
		Plugin_Scr_FreeArray(&array);
	}

	void Linq::Repeat()
	{
		CHECK_PARAMS(2, "Usage: Repeat(<array>, <count>)\n");

		VariableValueArray array = Plugin_Scr_GetArray(0);
		const int count = Plugin_Scr_GetInt(1);

		Plugin_Scr_MakeArray();
		for (int r = 0; r < count; r++)
		{
			for (int i = 0; i < array.length; i++)
			{
				Plugin_Scr_AddVariable(array.items[i]);
				Plugin_Scr_AddArray();
			}
		}
		Plugin_Scr_FreeArray(&array);
	}

	void Linq::Concat()
	{
		CHECK_PARAMS(2, "Usage: Concat(<arraySource>, <array>)\n");

		VariableValueArray arraySource = Plugin_Scr_GetArray(0);
		VariableValueArray array = Plugin_Scr_GetArray(1);

		Plugin_Scr_MakeArray();
		for (int i = 0; i < arraySource.length; i++)
		{
			Plugin_Scr_AddVariable(arraySource.items[i]);
			Plugin_Scr_AddArray();
		}
		for (int i = 0; i < array.length; i++)
		{
			Plugin_Scr_AddVariable(array.items[i]);
			Plugin_Scr_AddArray();
		}
		Plugin_Scr_FreeArray(&arraySource);
		Plugin_Scr_FreeArray(&array);
	}

	void Linq::Chunk()
	{
		CHECK_PARAMS(2, "Usage: Chunk(<array>, <count>)\n");

		VariableValueArray array = Plugin_Scr_GetArray(0);
		const int count = Plugin_Scr_GetInt(1);

		Plugin_Scr_MakeArray();
		for (int i = 0; i < array.length && count; i++)
		{
			if (!(i % count))
				Plugin_Scr_MakeArray();

			Plugin_Scr_AddVariable(array.items[i]);
			Plugin_Scr_AddArray();

			if (!((i + 1) % count) || i + 1 == array.length)
				Plugin_Scr_AddArray();
		}
		Plugin_Scr_FreeArray(&array);
	}

	bool Linq::CompareValues(const VariableValue& a, const VariableValue& b)
	{
		if (a.type != b.type)
			return false;

		switch (a.type)
		{
		case VAR_VECTOR:
			return a.u.vectorValue[0] == b.u.vectorValue[0] && a.u.vectorValue[1] == b.u.vectorValue[1]
				&& a.u.vectorValue[2] == b.u.vectorValue[2];
		case VAR_INTEGER:
			return a.u.intValue == b.u.intValue;
		case VAR_FLOAT:
			return a.u.floatValue == b.u.floatValue;
		case VAR_ISTRING:
		case VAR_STRING:
			return std::strcmp(Plugin_SL_ConvertToString(a.u.stringValue), Plugin_SL_ConvertToString(b.u.stringValue))
				== 0;
		case VAR_POINTER:
			return a.u.pointerValue == b.u.pointerValue;
		default:
			return false;
		}
	}

	void Linq::Contains()
	{
		CHECK_PARAMS(2, "Usage: Contains(<array>, <element>)\n");

		VariableValueArray array = Plugin_Scr_GetArray(0);
		VariableValue element = *Plugin_Scr_SelectParam(1);
		qboolean found = qfalse;

		for (int i = 0; i < array.length; i++)
		{
			if (CompareValues(array.items[i], element))
			{
				found = qtrue;
				break;
			}
		}
		Plugin_Scr_AddBool(found);
	}

	void Linq::IndexOf()
	{
		CHECK_PARAMS(2, "Usage: IndexOf(<array>, <element>)\n");

		VariableValueArray array = Plugin_Scr_GetArray(0);
		VariableValue element = *Plugin_Scr_SelectParam(1);
		int found = -1;

		for (int i = 0; i < array.length; i++)
		{
			if (CompareValues(array.items[i], element))
			{
				found = i;
				break;
			}
		}
		Plugin_Scr_FreeArray(&array);
		Plugin_Scr_AddInt(found);
	}

	void Linq::Remove()
	{
		CHECK_PARAMS(2, "Usage: Remove(<array>, <element>)\n");

		VariableValueArray array = Plugin_Scr_GetArray(0);
		VariableValue element = *Plugin_Scr_SelectParam(1);

		Plugin_Scr_MakeArray();
		for (int i = 0; i < array.length; i++)
		{
			if (!CompareValues(array.items[i], element))
			{
				Plugin_Scr_AddVariable(array.items[i]);
				Plugin_Scr_AddArray();
			}
		}
		Plugin_Scr_FreeArray(&array);
	}

	void Linq::RemoveAt()
	{
		CHECK_PARAMS(2, "Usage: RemoveAt(<array>, <index>)\n");

		VariableValueArray array = Plugin_Scr_GetArray(0);
		int index = Plugin_Scr_GetInt(1);

		Plugin_Scr_MakeArray();
		for (int i = 0; i < array.length; i++)
		{
			if (i == index)
				continue;

			Plugin_Scr_AddVariable(array.items[i]);
			Plugin_Scr_AddArray();
		}
		Plugin_Scr_FreeArray(&array);
	}
}
