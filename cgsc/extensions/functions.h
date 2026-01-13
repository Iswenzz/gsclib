#pragma once
#include "CGSC/cgsc.h"

__attribute__((used)) static int __callArgNumber = 0;
#define FLOAT(val) Scr_SetParamGeneric(__callArgNumber, val, VAR_FLOAT)
#define INT(val) Scr_SetParamGeneric(__callArgNumber, val, VAR_INTEGER)
#define VECTOR(val) Scr_SetParamGeneric(__callArgNumber, val, VAR_VECTOR)
#define POINTER(val) Scr_SetParamGeneric(__callArgNumber, val, VAR_POINTER)
#define STRING(val) Scr_SetParamGeneric(__callArgNumber, val, VAR_STRING)
#define ISTRING(val) Scr_SetParamGeneric(__callArgNumber, val, VAR_ISTRING)
#define FUNC(val) Scr_SetParamGeneric(__callArgNumber, val, VAR_FUNCTION)
#define UNDEFINED() Scr_SetParamGeneric(__callArgNumber, NULL, VAR_UNDEFINED)

EXPORT(qboolean, Scr_SetParamGeneric(unsigned int paramnum, void *var, int type));
EXPORT(void, Scr_CallFunction(void (*function)(void), ...));
EXPORT(void, Scr_CallMethod(void (*function)(scr_entref_t), scr_entref_t ent, ...));
EXPORT(int, Scr_GetThreadReturn());

void GScr_Test(scr_entref_t entref);
