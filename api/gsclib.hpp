#pragma once

#ifndef PLUGIN
	#include <q_shared.h>
	#include <cscr_main.h>
	#include <cscr_variable.h>
	#include <cscr_stringlist.h>
	#include <scr_vm.h>
	#include <sys_main.h>
#endif

#define EXPORT(type, definition) \
	type definition;             \
	type Plugin_##definition

#define VAR_MASK 0x1F
#define VAR_NAME_BITS 8

#define VARIABLELIST_CHILD_BEGIN 0x8002
#define VARIABLELIST_PARENT_BEGIN 0x1
#define VARIABLELIST_CHILD_SIZE 0xFFFE
#define VARIABLELIST_PARENT_SIZE 0x8000

extern "C"
{
	struct VariableValueArray
	{
		uint32_t length;
		VariableValue *items;
	};

	enum VariableValueTypeFlags
	{
		FLAG_UNDEFINED = 1,
		FLAG_BEGIN_REF = 2,
		FLAG_POINTER = 4,
		FLAG_STRING = 8,
		FLAG_ISTRING = 16,
		FLAG_VECTOR = 32,
		FLAG_END_REF = 64,
		FLAG_FLOAT = 128,
		FLAG_INTEGER = 256,
		FLAG_CODEPOS = 512,
		FLAG_PRECODEPOS = 1024,
		FLAG_FUNCTION = 2048,
		FLAG_STACK = 4096,
		FLAG_ANIMATION = 8192,
		FLAG_DEVELOPER_CODEPOS = 16384,
		FLAG_INCLUDE_CODEPOS = 32768,
		FLAG_THREAD = 65536,
		FLAG_NOTIFY_THREAD = 131072,
		FLAG_TIME_THREAD = 262144,
		FLAG_CHILD_THREAD = 524288,
		FLAG_OBJECT = 1048576,
		FLAG_DEAD_ENTITY = 2097152,
		FLAG_ENTITY = 4194304,
		FLAG_ARRAY = 8388608,
		FLAG_DEAD_THREAD = 16777216,
		FLAG_COUNT = 33554432,
		FLAG_THREAD_LIST = 67108864,
		FLAG_ENDON_LIST = 134217728
	};

	EXPORT(VariableValueArray, Scr_CreateArray(int length));
	EXPORT(void, Scr_FreeArray(VariableValueArray *array));
	EXPORT(VariableValueArray, Scr_GetArray(unsigned int paramnum));
	EXPORT(void, Scr_AddVariable(VariableValue var));
	EXPORT(void, Scr_AddPointerArray(unsigned int pointerValue));
	EXPORT(void, Scr_AddFunc(const char *codePosValue));
	EXPORT(unsigned short, Scr_ExecThreadResult(int handle, unsigned int paramcount));
	EXPORT(VariableValue, Scr_GetThreadResult());
	EXPORT(VariableValue *, Scr_GetTop(unsigned int paramnum));
	EXPORT(VariableValue *, Scr_SelectParam(unsigned int paramnum));
	EXPORT(uint32_t, Scr_GetArrayFlags(VariableValueArray array));
	EXPORT(unsigned int, Scr_GetObjectType(unsigned int id));
}
