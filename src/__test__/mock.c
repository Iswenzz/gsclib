#include "mock.h"

#include <cgsc.h>
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
    assert(msg);
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

const char* Plugin_SL_ConvertToString(int index)
{
    return "string";
}
