#include "gsclib.hpp"

extern "C"
{
	extern struct scrVarGlob_t gScrVarGlob;
	extern void IncInParam();
	extern void Scr_AddIString(const char* value);

	struct __attribute__((aligned(64))) scrVarGlob_t
	{
		VariableValueInternal* variableList;
	};

	VariableValueArray Scr_CreateArray(int length)
	{
		VariableValueArray array;
		array.length = length;
		array.items = new VariableValue[length];
		return array;
	}

	void Scr_FreeArray(VariableValueArray* array)
	{
		if (array && array->items)
		{
			delete[] array->items;
			array->items = nullptr;
		}
	}

	VariableValueArray Scr_GetArray(unsigned int paramnum)
	{
		VariableValueArray array = { 0, nullptr };
		int parentId = Scr_GetObject(paramnum);

		if (Scr_GetObjectType(parentId) != VAR_ARRAY)
			return array;

		int length = GetArraySize(parentId);
		int index = length - 1;

		if (!length)
			return array;

		VariableValueInternal* entryValue;
		array = Scr_CreateArray(length);
		unsigned int id = gScrVarGlob.variableList[parentId + VARIABLELIST_PARENT_BEGIN].nextSibling;
		unsigned int nextSibling;

		if (id)
		{
			while (true)
			{
				entryValue = &gScrVarGlob.variableList[id + VARIABLELIST_CHILD_BEGIN];

				array.items[index].type = entryValue->w.type & VAR_MASK;
				array.items[index].u = entryValue->u.u;

				nextSibling = gScrVarGlob.variableList[id + VARIABLELIST_CHILD_BEGIN].nextSibling;
				if (!nextSibling)
					break;

				id = gScrVarGlob.variableList[nextSibling + VARIABLELIST_CHILD_BEGIN].hash.id;
				index--;
			}
		}
		return array;
	}

	void Scr_AddPointerArray(unsigned int pointerValue)
	{
		if (Scr_GetObjectType(pointerValue) != VAR_ARRAY)
			return;

		int length = GetArraySize(pointerValue);
		int index = length - 1;

		if (!length)
		{
			Scr_MakeArray();
			return;
		}
		auto* entries = new VariableValueInternal[length];
		unsigned int id = gScrVarGlob.variableList[pointerValue + VARIABLELIST_PARENT_BEGIN].nextSibling;
		unsigned int nextSibling;

		if (id)
		{
			while (true)
			{
				entries[index] = gScrVarGlob.variableList[id + VARIABLELIST_CHILD_BEGIN];
				nextSibling = gScrVarGlob.variableList[id + VARIABLELIST_CHILD_BEGIN].nextSibling;

				if (!nextSibling)
					break;

				id = gScrVarGlob.variableList[nextSibling + VARIABLELIST_CHILD_BEGIN].hash.id;
				index--;
			}
		}
		Scr_MakeArray();

		for (int i = 0; i < length; i++)
		{
			VariableValue value;
			value.type = entries[i].w.type & VAR_MASK;
			value.u = entries[i].u.u;
			Scr_AddVariable(value);

			VariableValue indexerValue = Scr_GetArrayIndexValue(entries[i].w.name >> VAR_NAME_BITS);
			if (indexerValue.type == VAR_STRING)
				Scr_AddArrayStringIndexed(indexerValue.u.stringValue);
			else if (indexerValue.type == VAR_INTEGER)
				Scr_AddArray();
		}
		delete[] entries;
	}

	void Scr_AddFunc(const char* codePosValue)
	{
		IncInParam();
		gScrVmPub.top->type = VAR_FUNCTION;
		gScrVmPub.top->u.codePosValue = codePosValue;
	}

	VariableValue Scr_GetThreadResult()
	{
		VariableValue* returnRef = Scr_GetTop(-1);
		VariableValue var = *returnRef;
		returnRef->type = 0;
		return var;
	}

	VariableValue* Scr_GetTop(unsigned int paramnum)
	{
		return &gScrVmPub.top[-paramnum];
	}

	VariableValue* Scr_SelectParam(unsigned int paramnum)
	{
		if (paramnum >= gScrVmPub.outparamcount)
		{
			Scr_Error(const_cast<char*>("parameter does not exist\n"));
			return nullptr;
		}
		return Scr_GetTop(paramnum);
	}

	void Scr_AddVariable(VariableValue var)
	{
		switch (var.type)
		{
		case VAR_POINTER:
			switch (Scr_GetObjectType(var.u.pointerValue))
			{
			case VAR_ARRAY:
				Scr_AddPointerArray(var.u.pointerValue);
				break;
			case VAR_OBJECT:
			case VAR_ENTITY:
				Scr_AddObject(var.u.pointerValue);
				break;
			case VAR_UNDEFINED:
			default:
				Scr_AddUndefined();
				break;
			}
			break;
		case VAR_FUNCTION:
			Scr_AddFunc(var.u.codePosValue);
			break;
		case VAR_ISTRING:
			Scr_AddIString(SL_ConvertToString(var.u.stringValue));
			break;
		case VAR_FLOAT:
			Scr_AddFloat(var.u.floatValue);
			break;
		case VAR_INTEGER:
			Scr_AddInt(var.u.intValue);
			break;
		case VAR_STRING:
			Scr_AddString(SL_ConvertToString(var.u.stringValue));
			break;
		case VAR_VECTOR:
		{
			const float* vec = var.u.vectorValue;
			vec3_t value = { vec[0], vec[1], vec[2] };
			Scr_AddVector(value);
			break;
		}
		case VAR_ENTITY:
			Scr_AddEntity(&g_entities[157 * var.u.entityOffset]);
			break;
		case VAR_UNDEFINED:
		default:
			Scr_AddUndefined();
			break;
		}
	}

	uint32_t Scr_GetArrayFlags(VariableValueArray array)
	{
		uint32_t flags = 0;
		for (unsigned int i = 0; i < array.length; i++)
		{
			switch (array.items[i].type)
			{
			case VAR_UNDEFINED:
				flags |= FLAG_UNDEFINED;
				break;
			case VAR_POINTER:
				flags |= FLAG_POINTER;
				break;
			case VAR_STRING:
				flags |= FLAG_STRING;
				break;
			case VAR_ISTRING:
				flags |= FLAG_ISTRING;
				break;
			case VAR_VECTOR:
				flags |= FLAG_VECTOR;
				break;
			case VAR_FLOAT:
				flags |= FLAG_FLOAT;
				break;
			case VAR_INTEGER:
				flags |= FLAG_INTEGER;
				break;
			case VAR_CODEPOS:
				flags |= FLAG_CODEPOS;
				break;
			case VAR_PRECODEPOS:
				flags |= FLAG_PRECODEPOS;
				break;
			case VAR_FUNCTION:
				flags |= FLAG_FUNCTION;
				break;
			case VAR_STACK:
				flags |= FLAG_STACK;
				break;
			case VAR_ANIMATION:
				flags |= FLAG_ANIMATION;
				break;
			case VAR_DEVELOPER_CODEPOS:
				flags |= FLAG_DEVELOPER_CODEPOS;
				break;
			case VAR_INCLUDE_CODEPOS:
				flags |= FLAG_INCLUDE_CODEPOS;
				break;
			case VAR_THREAD:
				flags |= FLAG_THREAD;
				break;
			case VAR_NOTIFY_THREAD:
				flags |= FLAG_NOTIFY_THREAD;
				break;
			case VAR_TIME_THREAD:
				flags |= FLAG_TIME_THREAD;
				break;
			case VAR_CHILD_THREAD:
				flags |= FLAG_CHILD_THREAD;
				break;
			case VAR_OBJECT:
				flags |= FLAG_OBJECT;
				break;
			case VAR_DEAD_ENTITY:
				flags |= FLAG_DEAD_ENTITY;
				break;
			case VAR_ENTITY:
				flags |= FLAG_ENTITY;
				break;
			case VAR_ARRAY:
				flags |= FLAG_ARRAY;
				break;
			case VAR_DEAD_THREAD:
				flags |= FLAG_DEAD_THREAD;
				break;
			case VAR_COUNT:
				flags |= FLAG_COUNT;
				break;
			case VAR_THREAD_LIST:
				flags |= FLAG_THREAD_LIST;
				break;
			case VAR_ENDON_LIST:
				flags |= FLAG_ENDON_LIST;
				break;
			}
		}
		return flags;
	}
}
