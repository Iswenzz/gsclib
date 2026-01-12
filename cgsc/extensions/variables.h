#pragma once
#include "CGSC/cgsc.h"

EXPORT(VariableValueArray, Scr_CreateArray(int length));
EXPORT(void, Scr_FreeArray(VariableValueArray* array));
EXPORT(VariableValueArray, Scr_GetArray(unsigned int paramnum));
EXPORT(VariableValue*, Scr_SelectParamOrDefault(unsigned int paramnum));
EXPORT(VariableValue*, Scr_SelectParam(unsigned int paramnum));
EXPORT(VariableValue*, Scr_GetTop(unsigned int paramnum));
EXPORT(VariableValue, Scr_ReturnResult());
EXPORT(short, Scr_ExecThreadResult(int callbackHook, unsigned int numArgs));
EXPORT(void, Scr_AddFunc(const char* codePosValue));
EXPORT(void, Scr_AddPointerArray(unsigned int pointerValue));
EXPORT(void, Scr_AddVariable(VariableValue var));
EXPORT(uint32_t, Scr_GetArrayFlags(VariableValueArray array));
EXPORT(unsigned int, Scr_GetObjectType(unsigned int id));
