#pragma once

#ifndef PLUGIN_INCLUDES
#include "../../pinc.h"
#endif

#ifdef _MSC_VER
typedef __int64 int64_t;
typedef __int32 int32_t;
typedef __int16 int16_t;
typedef __int8 int8_t;
typedef unsigned __int64 uint64_t;
typedef unsigned __int32 uint32_t;
typedef unsigned __int16 uint16_t;
typedef unsigned __int8 uint8_t;
#else
#include <stdint.h>
#endif

#ifndef SCR_ENTREF_DEFINED
#define SCR_ENTREF_DEFINED
typedef struct
{
	uint16_t entnum;
	uint16_t classnum;
} Plugin_Scr_entref_t;
#endif

enum $0E0E04F36A22A28F2C0A7A22DC12DAE9
{
	VAR_UNDEFINED = 0x0,
	VAR_BEGIN_REF = 0x1,
	VAR_POINTER = 0x1,
	VAR_STRING = 0x2,
	VAR_ISTRING = 0x3,
	VAR_VECTOR = 0x4,
	VAR_END_REF = 0x5,
	VAR_FLOAT = 0x5,
	VAR_INTEGER = 0x6,
	VAR_CODEPOS = 0x7,
	VAR_PRECODEPOS = 0x8,
	VAR_FUNCTION = 0x9,
	VAR_STACK = 0xA,
	VAR_ANIMATION = 0xB,
	VAR_DEVELOPER_CODEPOS = 0xC,
	VAR_INCLUDE_CODEPOS = 0xD,
	VAR_THREAD = 0xE,
	VAR_NOTIFY_THREAD = 0xF,
	VAR_TIME_THREAD = 0x10,
	VAR_CHILD_THREAD = 0x11,
	VAR_OBJECT = 0x12,
	VAR_DEAD_ENTITY = 0x13,
	VAR_ENTITY = 0x14,
	VAR_ARRAY = 0x15,
	VAR_DEAD_THREAD = 0x16,
	VAR_COUNT = 0x17,
	VAR_THREAD_LIST = 0x18,
	VAR_ENDON_LIST = 0x19
};

enum GSCTypeFlag
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

struct VariableStackBuffer
{
	const char *pos;
	uint16_t size;
	uint16_t bufLen;
	uint16_t localId;
	char time;
	char buf[1];
};

union VariableUnion 
{
	int intValue;
	float floatValue;
	unsigned int stringValue;
	const float *vectorValue;
	const char *codePosValue;
	unsigned int pointerValue;
	struct VariableStackBuffer *stackValue;
	unsigned int entityOffset;
};

typedef struct
{
	union VariableUnion u;
	int type;
} VariableValue;

__attribute__((unused)) static int __callArgNumber = 0;

#define FLOAT(val) Plugin_Scr_SetParamFloat(__callArgNumber, val)
#define INT(val) Plugin_Scr_SetParamInt(__callArgNumber, val)
#define VECTOR(val) Plugin_Scr_SetParamVector(__callArgNumber, val)
#define OBJECT(val) Plugin_Scr_SetParamObject(__callArgNumber, val)
#define ENTITY(val) Plugin_Scr_SetParamEntity(__callArgNumber, val)
#define STRING(val) Plugin_Scr_SetParamString(__callArgNumber, val)
#define ISTRING(val) Plugin_Scr_SetParamIString(__callArgNumber, val)
#define FUNC(val) Plugin_Scr_SetParamFunc(__callArgNumber, val)
#define UNDEFINED() Plugin_Scr_SetParamUndefined(__callArgNumber)

void Plugin_Scr_FreeArray(VariableValue **array, int length);
VariableValue **Plugin_Scr_GetArray(unsigned int paramnum);
VariableValue *Plugin_Scr_AllocVariable(VariableValue *varRef);
VariableValue *Plugin_Scr_SelectParamOrDefault(unsigned int paramnum);
VariableValue *Plugin_Scr_SelectParam(unsigned int paramnum);
qboolean Plugin_Scr_SetParamFloat(unsigned int paramnum, float value);
qboolean Plugin_Scr_SetParamInt(unsigned int paramnum, int value);
qboolean Plugin_Scr_SetParamObject(unsigned int paramnum, int structPointer);
qboolean Plugin_Scr_SetParamEntity(unsigned int paramnum, int entID);
qboolean Plugin_Scr_SetParamIString(unsigned int paramnum, const char *string);
qboolean Plugin_Scr_SetParamString(unsigned int paramnum, const char *string);
qboolean Plugin_Scr_SetParamFunc(unsigned int paramnum, const char *codePos);
qboolean Plugin_Scr_SetParamStack(unsigned int paramnum, struct VariableStackBuffer *stack);
qboolean Plugin_Scr_SetParamVector(unsigned int paramnum, const float *value);
qboolean Plugin_Scr_SetParamUndefined(unsigned int paramnum);
int Plugin_Scr_GetFunc(unsigned int paramnum);
void Plugin_Scr_AddFunc(const char *codePosValue);
void Plugin_Scr_AddVariable(VariableValue *var);
void Plugin_Scr_CallFunction(void (*function)(void), ...);
void Plugin_Scr_CallMethod(void (*function)(Plugin_Scr_entref_t), Plugin_Scr_entref_t ent, ...);