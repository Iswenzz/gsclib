#pragma once

#ifndef PLUGIN_INCLUDES
#include "../../../pinc.h"
#endif

#ifdef PLUGIN_HANDLER_VERSION_MAJOR
    #if PLUGIN_HANDLER_VERSION_MAJOR >= 4
		#define _CGSC_4
    #elif PLUGIN_HANDLER_VERSION_MAJOR >= 3
		#define _CGSC_3
    #endif
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

typedef struct
{
    uint32_t length;
    VariableValue **items;
} VariableValueArray;

// ------------------------------ cgsc_utils ------------------------------ //
/**
 * @brief Create a formated string,
 * The buffer variable is named "cgsc_va".
 */
#define CGSC_va(fmt,...) 							    \
char cgsc_va[1024];									    \
snprintf(cgsc_va, sizeof(cgsc_va), fmt, __VA_ARGS__);   \

/**
 * @brief Get the flags from GSC array object.
 * 
 * @param array - The GSC array.
 * @return uint32_t - Flags value.
 */
uint32_t Plugin_GetFlagsFromGSCArray(VariableValueArray *array);

// ------------------------------ cgsc_param ------------------------------ //

/**
 * @brief 
 * This variable is used to keep track of param count for a single call, 
 * and can only be used in non-thread safe environment.
 * @todo 
 */
__attribute__((used)) static int __callArgNumber = 0;

/**
 * @brief Alloc a new GSC float param before calling the function with Scr_CallFunction/Scr_CallMethod.
 */
#define FLOAT(val) Plugin_Scr_SetParamGeneric(__callArgNumber, val, VAR_FLOAT)
/**
 * @brief Alloc a new GSC int param before calling the function with Scr_CallFunction/Scr_CallMethod.
 */
#define INT(val) Plugin_Scr_SetParamGeneric(__callArgNumber, val, VAR_INTEGER)
/**
 * @brief Alloc a new GSC vector param before calling the function with Scr_CallFunction/Scr_CallMethod.
 */
#define VECTOR(val) Plugin_Scr_SetParamGeneric(__callArgNumber, val, VAR_VECTOR)
/**
 * @brief Alloc a new GSC pointer param before calling the function with Scr_CallFunction/Scr_CallMethod.
 */
#define POINTER(val) Plugin_Scr_SetParamGeneric(__callArgNumber, val, VAR_POINTER)
/**
 * @brief Alloc a new GSC string param before calling the function with Scr_CallFunction/Scr_CallMethod.
 */
#define STRING(val) Plugin_Scr_SetParamGeneric(__callArgNumber, val, VAR_STRING)
/**
 * @brief Alloc a new GSC localized string param before calling the function with Scr_CallFunction/Scr_CallMethod.
 */
#define ISTRING(val) Plugin_Scr_SetParamGeneric(__callArgNumber, val, VAR_ISTRING)
/**
 * @brief Alloc a new GSC function param before calling the function with Scr_CallFunction/Scr_CallMethod.
 */
#define FUNC(val) Plugin_Scr_SetParamGeneric(__callArgNumber, val, VAR_FUNCTION)
/**
 * @brief Alloc a new GSC undefined param before calling the function with Scr_CallFunction/Scr_CallMethod.
 */
#define UNDEFINED() Plugin_Scr_SetParamGeneric(__callArgNumber, NULL, VAR_UNDEFINED)

/**
 * @brief Alloc a new GSC generic param before calling the function with Scr_CallFunction/Scr_CallMethod.
 * 
 * @param paramnum - The param index to alloc.
 * @param var - The value of the generic variable.
 * @param type - The type of the generic variable.
 * @return qboolean - Boolean result.
 */
qboolean Plugin_Scr_SetParamGeneric(unsigned int paramnum, void *var, int type);

/**
 * @brief Call the specified GSC function pointer
 * This function is experimental. @todo
 * @param function - The GSC function pointer.
 * @param ... - GSC alloc macros can be written here only for convenience.
 */
void Plugin_Scr_CallFunction(void (*function)(void), ...);

/**
 * @brief Call the specified GSC method pointer
 * This function is experimental. @todo
 * @param function - The GSC function pointer.
 * @param ent - The GSC entref.
 * @param ... - GSC alloc macros can be written here only for convenience.
 */
void Plugin_Scr_CallMethod(void (*function)(scr_entref_t), scr_entref_t ent, ...);

// ----------------------------- cgsc_variable ---------------------------- //
/**
 * @brief Free a VariableValueArray and its values.
 * 
 * @param array - The VariableValueArray to free.
 */
void Plugin_Scr_FreeArray(VariableValueArray *array);

/**
 * @brief Get a GSC array from specified param number.
 * 
 * @param paramnum - GSC param number.
 * @return VariableValueArray* - The GSC array.
 */
VariableValueArray *Plugin_Scr_GetArray(unsigned int paramnum);

/**
 * @brief Alloc a VariableValue* and copy the variable info from specified parameter.
 * Call free() when the value is not used anymore.
 * 
 * @param varRef - The variable to copy.
 * @return VariableValue* - A copy of the variable.
 */
VariableValue *Plugin_Scr_AllocVariable(VariableValue *varRef);

/**
 * @brief Get a GSC variable reference from the specified param number.
 * If the param number is not found it will allocate a default one.
 * 
 * @param paramnum - GSC param number.
 * @return VariableValue* - GSC variable reference.
 */
VariableValue *Plugin_Scr_SelectParamOrDefault(unsigned int paramnum);

/**
 * @brief Get a GSC variable reference from the specified param number.
 * 
 * @param paramnum - GSC param number.
 * @return VariableValue* - GSC variable reference.
 */
VariableValue *Plugin_Scr_SelectParam(unsigned int paramnum);

/**
 * @brief Get a GSC variable reference from the GSC stack with the specified index.
 * 
 * @param paramnum - Index to get from the GSC stack.
 * @return VariableValue* - GSC variable reference.
 */
VariableValue *Plugin_Scr_GetTop(unsigned int paramnum);

/**
 * @brief Alloc a copy of the last GSC return variable.
 * Call free() when the value is not used anymore.
 * 
 * @return VariableValue* - The allocated variable.
 */
VariableValue *Plugin_Scr_AllocReturnResult();

/**
 * @brief Call a GSC function and keep the GSC return value uncleared.
 * 
 * @param callbackHook - GSC function ID.
 * @param numArgs - GSC function args count.
 * @return short - The GSC thread id to be freed with Scr_FreeThread(<short>).
 */
short Plugin_Scr_ExecThreadResult(int callbackHook, unsigned int numArgs);

/**
 * @brief Return a GSC Function from specified codeposvalue.
 * This function is untested.
 * 
 * @param codePosValue 
 */
void Plugin_Scr_AddFunc(const char *codePosValue);

/**
 * @brief Return a GSC variable.
 * 
 * @param var - The GSC variable to return.
 */
void Plugin_Scr_AddVariable(VariableValue *var);

/**
 * @brief Print GSC variable informations.
 * 
 * @param var - The GSC variable to debug.
 */
void Plugin_Scr_DebugVariable(VariableValue *var);

// ------------------------------ cgsc_export ----------------------------- //
/**
 * @brief Get the type of a GSC object.
 * 
 * @param id - The GSC object.
 * @return unsigned int - The type enum.
 */
unsigned int Plugin_Scr_GetObjectType(unsigned int id);

/**
 * @brief Get GSC func id from specified param num.
 * 
 * @param paramnum - GSC param index.
 * @return int - The GSC func id.
 */
int Plugin_Scr_GetFunc(unsigned int paramnum);