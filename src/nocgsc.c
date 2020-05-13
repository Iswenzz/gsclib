#include <cgsc.h>

#define UNSUPPORTED_ERROR() \
Plugin_Scr_Error("ERROR: This function needs the CGSC extension.");

#define UNSUPPORTED_ERROR_RET(x)                                    \
Plugin_Scr_Error("ERROR: This function needs the CGSC extension."); \
return x;

#ifdef _NO_CGSC

void Plugin_Scr_CallFunction(void (*function)(void), ...)                           { UNSUPPORTED_ERROR(); }
void Plugin_Scr_CallMethod(void (*function)(scr_entref_t), scr_entref_t ent, ...)   { UNSUPPORTED_ERROR(); }
void Plugin_Scr_FreeArray(VariableValueArray *array)                                { UNSUPPORTED_ERROR(); }
void Plugin_Scr_AddFunc(const char *codePosValue)                                   { UNSUPPORTED_ERROR(); }
void Plugin_Scr_AddVariable(VariableValue *var)                                     { UNSUPPORTED_ERROR(); }
void Plugin_Scr_DebugVariable(VariableValue *var)                                   { UNSUPPORTED_ERROR(); }
qboolean Plugin_Scr_SetParamGeneric(unsigned int paramnum, void *var, int type)     { UNSUPPORTED_ERROR_RET(qfalse); }
VariableValueArray *Plugin_Scr_GetArray(unsigned int paramnum)                      { UNSUPPORTED_ERROR_RET(NULL); }
VariableValue *Plugin_Scr_AllocVariable(VariableValue *varRef)                      { UNSUPPORTED_ERROR_RET(NULL); }
VariableValue *Plugin_Scr_SelectParamOrDefault(unsigned int paramnum)               { UNSUPPORTED_ERROR_RET(NULL); }
VariableValue *Plugin_Scr_SelectParam(unsigned int paramnum)                        { UNSUPPORTED_ERROR_RET(NULL); }
VariableValue *Plugin_Scr_GetTop(unsigned int paramnum)                             { UNSUPPORTED_ERROR_RET(NULL); }
VariableValue *Plugin_Scr_AllocReturnResult()                                       { UNSUPPORTED_ERROR_RET(NULL); }
short Plugin_Scr_ExecThreadResult(int callbackHook, unsigned int numArgs)           { UNSUPPORTED_ERROR_RET(0); }
unsigned int Plugin_Scr_GetObjectType(unsigned int id)                              { UNSUPPORTED_ERROR_RET(0); }
int Plugin_Scr_GetFunc(unsigned int paramnum)                                       { UNSUPPORTED_ERROR_RET(0); }
uint32_t Plugin_GetFlagsFromGSCArray(VariableValueArray *array)                     { UNSUPPORTED_ERROR_RET(0); }

#endif
