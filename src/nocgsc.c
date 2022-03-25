#include <cgsc.h>

#define UNSUPPORTED(definition)											\
definition																\
{																		\
	Plugin_Scr_Error("ERROR: This function needs the CGSC extension."); \
}

#define UNSUPPORTED_RETURN(value, definition)							\
definition																\
{																		\
	Plugin_Scr_Error("ERROR: This function needs the CGSC extension."); \
	return value;														\
}

#ifdef CGSC_DISABLED
UNSUPPORTED(void Plugin_Scr_CallFunction(void (*function)(void), ...));
UNSUPPORTED(void Plugin_Scr_CallMethod(void (*function)(scr_entref_t), scr_entref_t ent, ...);
UNSUPPORTED(void Plugin_Scr_FreeArray(VariableValueArray* array));
UNSUPPORTED(void Plugin_Scr_AddFunc(const char* codePosValue));
UNSUPPORTED(void Plugin_Scr_AddVariable(VariableValue* var));
UNSUPPORTED(void Plugin_Scr_DebugVariable(VariableValue* var));
UNSUPPORTED_RETURN(false, qboolean Plugin_Scr_SetParamGeneric(unsigned int paramnum, void* var, int type));
UNSUPPORTED_RETURN(NULL, VariableValueArray* Plugin_Scr_GetArray(unsigned int paramnum));
UNSUPPORTED_RETURN(NULL, VariableValue *Plugin_Scr_AllocVariable(VariableValue *varRef));
UNSUPPORTED_RETURN(NULL, VariableValue *Plugin_Scr_SelectParamOrDefault(unsigned int paramnum));
UNSUPPORTED_RETURN(NULL, VariableValue *Plugin_Scr_SelectParam(unsigned int paramnum));
UNSUPPORTED_RETURN(NULL, VariableValue *Plugin_Scr_GetTop(unsigned int paramnum));
UNSUPPORTED_RETURN(NULL, VariableValue *Plugin_Scr_AllocReturnResult());
UNSUPPORTED_RETURN(0, short Plugin_Scr_ExecThreadResult(int callbackHook, unsigned int numArgs));
UNSUPPORTED_RETURN(0, unsigned int Plugin_Scr_GetObjectType(unsigned int id));
UNSUPPORTED_RETURN(0, int Plugin_Scr_GetFunc(unsigned int paramnum));
UNSUPPORTED_RETURN(0, uint32_t Plugin_GetFlagsFromGSCArray(VariableValueArray *array));
#endif
