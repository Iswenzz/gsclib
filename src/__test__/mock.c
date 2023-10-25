#include <CGSC/cgsc.h>

#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <assert.h>

void Plugin_Printf(const char* fmt, ...)
{
    va_list argptr;
    va_start(argptr, fmt);
    printf(fmt, argptr);
    va_end(argptr);
}

void Plugin_Scr_Error(const char* msg)
{
    printf("%s\n", msg);
}

async_handler* Plugin_AsyncInit()
{
    return NULL;
}

void Plugin_AsyncShutdown(async_handler* handler)
{

}

async_worker* Plugin_AsyncWorker(async_handler* handler, void* data, uv_work_cb callback, uv_after_work_cb afterCallback)
{
    return NULL;
}

void Plugin_AsyncWorkerDone(uv_work_t* req, async_status status)
{

}

qboolean Plugin_CGSC_UnsupportedMessage(qboolean versionCondition, char* format, ...)
{
    return qfalse;
}

float Plugin_CGSC_Version()
{
    return 0.0f;
}

client_t* Plugin_GetClientForClientNum(int clientnum)
{
    return NULL;
}

gentity_t* Plugin_GetGentityForEntityNum(int entnum)
{
    return NULL;
}

int Plugin_Milliseconds()
{
    return 0;
}

const char* Plugin_NET_AdrToStringShortMT(netadr_t* a, char* buf, int len)
{
    return NULL;
}

const char* Plugin_SL_ConvertToString(int index)
{
    return NULL;
}

void Plugin_Scr_AddVariable(VariableValue var)
{

}

void Plugin_Scr_AddVector(vec3_t vec)
{

}

void Plugin_Scr_AddArray()
{

}

void Plugin_Scr_AddArrayStringIndexed(int strIdx)
{

}

void Plugin_Scr_AddBool(qboolean value)
{

}

void Plugin_Scr_AddFloat(float value)
{

}

void Plugin_Scr_AddInt(int value)
{

}

void Plugin_Scr_AddString(const char* string)
{

}

void Plugin_Scr_AddUndefined()
{

}

int Plugin_Scr_AllocString(const char* string)
{
    return 0;
}

void Plugin_Scr_CallFunction(void (*function)(void), ...)
{

}

void Plugin_Scr_CallMethod(void (*function)(scr_entref_t), scr_entref_t ent, ...)
{

}

short Plugin_Scr_ExecThread(int callbackHook, unsigned int numArgs)
{
    return 0;
}

void Plugin_Scr_FreeThread(short threadId)
{

}

int Plugin_Scr_GetThreadReturn()
{
    return 0;
}

void Plugin_Scr_MakeArray()
{

}

void Plugin_Scr_ObjectError(const char* string)
{

}

void Plugin_Scr_ParamError(int paramnum, const char* string)
{

}

VariableValueArray Plugin_Scr_CreateArray(int length)
{
    VariableValueArray array;
    array.length = length;
    array.items = (VariableValue*)malloc(array.length * sizeof(VariableValue));
    return array;
}

void Plugin_Scr_FreeArray(VariableValueArray* array)
{
	free(array->items);
}

VariableValueArray Plugin_Scr_GetArray(unsigned int paramnum)
{
    VariableValueArray array = { 0 };
    return array;
}

uint32_t Plugin_Scr_GetArrayFlags(VariableValueArray array)
{
    return 0;
}

float Plugin_Scr_GetFloat(unsigned int paramnum)
{
    return 0.0f;
}

int Plugin_Scr_GetFunction(unsigned int paramnum)
{
    return 0;
}

int Plugin_Scr_GetInt(unsigned int paramnum)
{
    return 0;
}

int Plugin_Scr_GetNumParam()
{
    return 0;
}

unsigned int Plugin_Scr_GetObjectType(unsigned int id)
{
    return 0;
}

char* Plugin_Scr_GetString(unsigned int paramnum)
{
    return "";
}

VariableValue* Plugin_Scr_SelectParamOrDefault(unsigned int paramnum)
{
    return NULL;
}

VariableValue* Plugin_Scr_SelectParam(unsigned int paramnum)
{
    return NULL;
}

VariableValue* Plugin_Scr_GetTop(unsigned int paramnum)
{
    return NULL;
}

VariableValue Plugin_Scr_ReturnResult()
{
    VariableValue value = { 0 };
    return value;
}

short Plugin_Scr_ExecThreadResult(int callbackHook, unsigned int numArgs)
{
    return 0;
}

char* Plugin_Cmd_Argv(int arg)
{
	return NULL;
}

int Plugin_Cmd_Argc()
{
    return 0;
}

char* Plugin_Cmd_Args(char* buff, int bufsize)
{
    return NULL;
}

float Sys_GetCommonVersion()
{
    return 0.0f;
}
