#pragma once

#ifndef PLUGIN_INCLUDES
#include "../pinc.h"
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