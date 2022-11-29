#include "mock.h"

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

int Plugin_Scr_GetNumParam()
{
    return 0;
}

int Plugin_Scr_GetInt(unsigned int num)
{
    return 0;
}

char* Plugin_Scr_GetString(unsigned int num)
{
    return "string";
}

void Plugin_Scr_AddBool(qboolean value)
{
    
}

void Plugin_Scr_AddInt(int value)
{

}

void Plugin_Scr_AddString(const char* string)
{

}

void Plugin_Scr_AddArray()
{

}

void Plugin_Scr_MakeArray()
{

}

VariableValue* Plugin_Scr_SelectParam(unsigned int paramnum)
{
    return NULL;
}

void Plugin_Scr_AddVariable(VariableValue var)
{

}

unsigned int Plugin_Scr_GetObjectType(unsigned int id)
{
    return 0;
}

const char* Plugin_SL_ConvertToString(int index)
{
    return "string";
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
